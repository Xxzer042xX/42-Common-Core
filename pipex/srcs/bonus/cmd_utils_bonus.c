/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_bonus.c                                  :+:      :+:    :+:   */
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
/*   Fonction d'exécution d'une commande.                                     */
/*                                                                            */
/*   Processus d'exécution d'une commande :                                   */
/*   1. Parsing de la commande :                                              */
/*      "ls -la /tmp" devient ["ls", "-la", "/tmp", NULL]                     */
/*      Gère les guillemets : 'echo "Hello World"' -> ["echo", "Hello World"] */
/*                                                                            */
/*   2. Recherche du chemin :                                                 */
/*      - Vérifie si la commande contient un chemin (/bin/ls)                 */
/*      - Sinon, cherche dans les répertoires PATH                            */
/*      Exemple : "ls" -> "/bin/ls"                                           */
/*                                                                            */
/*   3. Exécution :                                                           */
/*      - Remplace le processus actuel par la nouvelle commande               */
/*      - Utilise les redirections configurées précédemment                   */
/*                                                                            */
/*   Gestion des erreurs :                                                    */
/*   - Échec de parsing : ERR_MALLOC                                          */
/*   - Commande non trouvée : ERR_CMD_NOT_FOUND                               */
/*   - Échec d'exécution : ERR_CMD_NOT_FOUND                                  */
/*                                                                            */
/*   Exemple d'utilisation :                                                  */
/*   execute_cmd(data, "grep 'pattern' -i", env);                             */
/*   -> Parse en ["grep", "pattern", "-i"]                                    */
/*   -> Trouve "/usr/bin/grep"                                                */
/*   -> Exécute avec les redirections configurées                             */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - cmd : chaîne de caractères contenant la commande et ses arguments      */
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
/*   Gestion des caractères spéciaux lors du parsing.                         */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Analyse les guillemets simples et doubles                             */
/*   2. Gère les caractères d'échappement                                     */
/*                                                                            */
/*   Étapes détaillées :                                                      */
/*   1. Vérification du type de guillemet                                     */
/*   2. Mise à jour de l'état du parsing                                      */
/*   3. Gestion des caractères d'échappement                                  */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : chaîne à analyser                                                */
/*   - i : position courante dans la chaîne                                   */
/*   - qtype : type de guillemet actif                                        */
/*   - esc : état d'échappement                                               */
/*                                                                            */
/*   Note : Retourne 1 si le caractère doit être ignoré, 0 sinon              */
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
/*   Extraction d'un token de la commande.                                    */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Alloue la mémoire pour le token                                       */
/*   2. Extrait les caractères jusqu'à un délimiteur                          */
/*   3. Gère les guillemets et échappements                                   */
/*                                                                            */
/*   Étapes détaillées :                                                      */
/*   1. Allocation mémoire                                                    */
/*   2. Copie des caractères avec gestion spéciale                            */
/*   3. Terminaison du token                                                  */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : chaîne source                                                    */
/*   - i : position de début                                                  */
/*   - qtype : type de guillemet actif                                        */
/*                                                                            */
/*   Note : Retourne NULL en cas d'erreur d'allocation                        */
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
/*   Analyse complète d'une commande.                                         */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Alloue le tableau d'arguments                                         */
/*   2. Parse la commande en tokens                                           */
/*   3. Vérifie la validité des guillemets                                    */
/*                                                                            */
/*   Étapes détaillées :                                                      */
/*   1. Allocation du tableau                                                 */
/*   2. Parsing des tokens                                                    */
/*   3. Vérification finale                                                   */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : commande à analyser                                              */
/*                                                                            */
/*   Note : Retourne NULL si erreur parsing ou allocation                     */
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
/*   Découpage de la commande en tokens.                                      */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Parcourt la chaîne de commande                                        */
/*   2. Extrait chaque token                                                  */
/*   3. Remplit le tableau d'arguments                                        */
/*                                                                            */
/*   Étapes détaillées :                                                      */
/*   1. Initialisation des compteurs                                          */
/*   2. Extraction des tokens                                                 */
/*   3. Terminaison du tableau                                                */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : commande à découper                                              */
/*   - args : tableau de destination                                          */
/*   - qtype : type de guillemet actif                                        */
/*                                                                            */
/*   Note : Retourne 0 si succès, -1 si erreur                                */
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
