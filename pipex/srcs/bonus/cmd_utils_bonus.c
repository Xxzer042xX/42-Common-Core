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

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'exécution d'une commande.                                     */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Sépare la commande et ses arguments                                   */
/*   2. Cherche le chemin complet de la commande                              */
/*   3. Exécute la commande avec execve                                       */
/*                                                                            */
/*   Étapes détaillées :                                                      */
/*   1. Analyse de la commande (parsing)                                      */
/*   2. Recherche du chemin dans PATH                                         */
/*   3. Exécution avec gestion des erreurs                                    */
/*   4. Libération de la mémoire en cas d'échec                               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - cmd : chaîne de caractères contenant la commande et ses arguments      */
/*   - env : variables d'environnement                                        */
/*                                                                            */
/*   Note : Cette fonction ne retourne jamais si l'exécution réussit          */
/*   En cas d'échec, elle libère la mémoire et appel ft_exit, qui             */
/*   termine le programme proprement                                          */
/*                                                                            */
/* ************************************************************************** */

void	execute_cmd(t_pipex *data, char *cmd, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		ft_exit("Error: Memory allocation failed", data, ERR_MALLOC);
	path = find_path(args[0], env);
	if (!path)
	{
		ft_free_split(args, 0);
		ft_exit("", data, ERR_CMD_NOT_FOUND);
	}
	if (execve(path, args, env) == -1)
	{
		free(path);
		ft_free_split(args, 0);
		ft_exit("Error: Command execution failed", data, ERR_CMD_NOT_FOUND);
	}
}

/*
void execute_cmd(t_pipex *data, char *cmd, char **env) {
    char *path;
    char **args;

    args = parse_command(cmd); // Utilise parse_command au lieu de ft_split
    if (!args)
        ft_exit("Error: Memory allocation failed", data, ERR_MALLOC);

    path = find_path(args[0], env);
    if (!path) {
        ft_free_split(args, 0);
        ft_exit("", data, ERR_CMD_NOT_FOUND);
    }

    if (execve(path, args, env) == -1) {
        free(path);
        ft_free_split(args, 0);
        ft_exit("Error: Command execution failed", data, ERR_CMD_NOT_FOUND);
    }
}



// Fonction pour ajouter un argument à la liste des résultats
static void add_argument(char **result, int *k, char *arg, int *j) {
    arg[*j] = '\0';
    result[(*k)++] = strdup(arg);
    *j = 0; // Réinitialise le buffer temporaire
}

// Fonction principale de parsing
char **parse_command(const char *cmd) {
    char **result = malloc(1024 * sizeof(char *)); // Taille arbitraire
    char *arg = malloc(1024);
    int i = 0, j = 0, k = 0; // i : index de cmd, j : index d'arg, k : index de result
    int in_quotes = 0;       // 0 = hors guillemets, 1 = dans les guillemets

    while (cmd[i]) {
        if (cmd[i] == '\'' || cmd[i] == '"') {
            in_quotes = !in_quotes; // Alterne l'état des guillemets
        } else if (cmd[i] == ' ' && !in_quotes) {
            if (j > 0) {
                add_argument(result, &k, arg, &j); // Ajoute l'argument à la liste
            }
        } else {
            arg[j++] = cmd[i];
        }
        i++;
    }
    if (j > 0) {
        add_argument(result, &k, arg, &j); // Ajoute le dernier argument
    }
    result[k] = NULL;

    free(arg);
    return result;
}
*/