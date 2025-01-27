/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:29:00 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/15 11:31:43 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static char	**parse_command(const char *cmd);
static char	*extract_token(const char *cmd, int *i, int *qtype);
static int	handle_quote_esc(const char *cmd, int *i, int *qtype, int *esc);
static int	parse_token(const char *cmd, char **args, int *qtype);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'exécution d'une commande dans le pipeline.                    */
/*                                                                            */
/*   Cette fonction gère les étapes finales de l'exécution :                  */
/*   1. Analyse de la commande avec parse_command                             */
/*      Ex: "ls -la /tmp" -> ["ls", "-la", "/tmp", NULL]                      */
/*                                                                            */
/*   2. Recherche du chemin avec find_path                                    */
/*      - Chemin absolu si présent (/bin/ls)                                  */
/*      - Recherche dans PATH sinon (ls -> /bin/ls)                           */
/*                                                                            */
/*   3. Exécution de la commande avec execve                                  */
/*      - Remplace le processus actuel                                        */
/*      - Utilise les redirections préalablement configurées                  */
/*                                                                            */
/*   Gestion d'erreurs :                                                      */
/*   - Échec de parse_command -> ERR_MALLOC                                   */
/*   - Commande non trouvée   -> ERR_CMD_NOT_FOUND                            */
/*   - Échec d'execve         -> ERR_CMD_NOT_FOUND                            */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - cmd : commande à exécuter (ex: "ls -la")                               */
/*   - env : variables d'environnement                                        */
/*                                                                            */
/* ************************************************************************** */
void	execute_cmd(t_pipex *data, char *cmd, char **env)
{
	char	*path;
	char	**args;

	args = parse_command(cmd);
	if (!args)
		ft_exit("Memory allocation failed", data, ERR_MALLOC);
	path = find_path(args[0], env);
	if (!path)
	{
		ft_free_split(args);
		ft_exit("Command not found", data, ERR_CMD_NOT_FOUND);
	}
	execve(path, args, env);
	free(path);
	ft_free_split(args);
	ft_exit("Command execution failed", data, ERR_CMD_NOT_FOUND);
}

/* ************************************************************************** */
/*                                                                            */
/*   Gestionnaire de guillemets et caractères d'échappement.                  */
/*                                                                            */
/*   Cette fonction détermine le traitement de chaque caractère :             */
/*   1. Guillemets (' ou ") :                                                 */
/*      - Active/désactive le mode guillemet approprié                        */
/*      - Ignore le caractère guillemet lui-même                              */
/*                                                                            */
/*   2. Caractère d'échappement (\) :                                         */
/*      - Active le mode échappement pour le prochain caractère               */
/*      - Permet d'inclure guillemets et espaces dans les arguments           */
/*                                                                            */
/*   Comportement selon contexte :                                            */
/*   - Hors guillemets : \ et guillemets sont spéciaux                        */
/*   - Dans guillemets : seul le guillemet correspondant est spécial          */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : chaîne en cours d'analyse                                        */
/*   - i : position actuelle                                                  */
/*   - qtype : type de guillemet actif (0, ' ou ")                            */
/*   - esc : état d'échappement                                               */
/*                                                                            */
/*   Retourne :                                                               */
/*   1 si caractère spécial (à ignorer), 0 sinon (à conserver)                */
/*                                                                            */
/* ************************************************************************** */
static int	handle_quote_esc(const char *cmd, int *i, int *qtype, int *esc)
{
	if (!*esc && ft_isquote(cmd[*i]) && \
		(!*qtype || cmd[*i] == *qtype))
	{
		if (!*qtype)
			*qtype = cmd[*i];
		else
			*qtype = 0;
		return (1);
	}
	if (!*esc && cmd[*i] == '\\')
	{
		*esc = 1;
		return (1);
	}
	*esc = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*   Extracteur d'arguments individuels d'une commande.                       */
/*                                                                            */
/*   Cette fonction isole un argument en :                                    */
/*   1. Allouant un buffer de 1024 caractères pour l'argument                 */
/*      - Taille fixe pour éviter les débordements                            */
/*      - Limite la taille maximum d'un argument                              */
/*                                                                            */
/*   2. Extrayant les caractères jusqu'à :                                    */
/*      - Un espace (hors guillemets)                                         */
/*      - La fin de la commande                                               */
/*      Tout en gérant :                                                      */
/*      - Les guillemets via handle_quote_esc                                 */
/*      - Les caractères échappés                                             */
/*                                                                            */
/*   Exemples d'extraction :                                                  */
/*   Dans "echo 'Hello World'" :                                              */
/*   - Premier appel : extrait "echo"                                         */
/*   - Second appel  : extrait "Hello World"                                  */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : commande source                                                  */
/*   - i : position actuelle (mise à jour après extraction)                   */
/*   - qtype : type de guillemet actif                                        */
/*                                                                            */
/*   Retourne :                                                               */
/*   - L'argument extrait (chaîne allouée)                                    */
/*   - NULL si échec d'allocation                                             */
/*                                                                            */
/* ************************************************************************** */
static char	*extract_token(const char *cmd, int *i, int *qtype)
{
	char	*token;
	int		j;
	int		escaped;

	token = malloc(sizeof(char) * 1024);
	if (!token)
		return (NULL);
	j = 0;
	escaped = 0;
	while (cmd[*i] && (cmd[*i] != ' ' || *qtype || escaped))
	{
		if (!handle_quote_esc(cmd, i, qtype, &escaped))
			token[j++] = cmd[*i];
		(*i)++;
	}
	token[j] = '\0';
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction principale d'analyse d'une commande shell.                      */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Alloue un tableau de 256 pointeurs pour les arguments                 */
/*      - Limite fixe de 256 arguments par commande                           */
/*      - Termine toujours par NULL pour execve                               */
/*                                                                            */
/*   2. Analyse la commande via parse_token                                   */
/*      - Découpe en respectant les guillemets et échappements                */
/*      - Vérifie que tous les guillemets sont fermés                         */
/*                                                                            */
/*   Exemples de parsing :                                                    */
/*   - "ls -la"          -> ["ls", "-la", NULL]                               */
/*   - "echo 'bonjour'"  -> ["echo", "bonjour", NULL]                         */
/*   - "grep \"motif\""  -> ["grep", "motif", NULL]                           */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Succès : tableau d'arguments terminé par NULL                          */
/*   - Échec : NULL (erreur allocation ou guillemets non fermés)              */
/*                                                                            */
/*   Paramètre :                                                              */
/*   - cmd : chaîne de commande à analyser                                    */
/*                                                                            */
/* ************************************************************************** */
static char	**parse_command(const char *cmd)
{
	char	**args;
	int		qtype;

	args = malloc(256 * sizeof(char *));
	if (!args)
		return (NULL);
	qtype = 0;
	if (parse_token(cmd, args, &qtype) == -1)
		return (ft_free_split(args), NULL);
	if (qtype != 0)
		return (ft_free_split(args), NULL);
	return (args);
}

/* ************************************************************************** */
/*                                                                            */
/*   Analyseur syntaxique des arguments d'une commande.                       */
/*                                                                            */
/*   Cette fonction découpe la commande en :                                  */
/*   1. Ignorant les espaces multiples entre arguments                        */
/*      - Avance jusqu'au prochain caractère non-espace                       */
/*      - Permet "cmd   arg" équivalent à "cmd arg"                           */
/*                                                                            */
/*   2. Extrayant chaque argument via extract_token                           */
/*      - Remplit le tableau args progressivement                             */
/*      - Vérifie chaque allocation                                           */
/*      - Termine le tableau par NULL                                         */
/*                                                                            */
/*   Exemples de découpage :                                                  */
/*   "echo   'Hello'   'World'" devient :                                     */
/*   args[0] = "echo"                                                         */
/*   args[1] = "Hello"                                                        */
/*   args[2] = "World"                                                        */
/*   args[3] = NULL                                                           */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : commande à découper                                              */
/*   - args : tableau de destination pour les arguments                       */
/*   - qtype : type de guillemet actif                                        */
/*                                                                            */
/*   Retourne :                                                               */
/*   - 0 si succès                                                            */
/*   - -1 si erreur d'allocation                                              */
/*                                                                            */
/* ************************************************************************** */
static int	parse_token(const char *cmd, char **args, int *qtype)
{
	int	i;
	int	arg_index;

	i = 0;
	arg_index = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		if (cmd[i])
		{
			args[arg_index] = extract_token(cmd, &i, qtype);
			if (!args[arg_index++])
				return (-1);
		}
	}
	args[arg_index] = NULL;
	return (0);
}
