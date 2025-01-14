/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_util_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:49:16 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 14:55:28 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de recherche du chemin complet d'une commande dans le PATH.     */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Ajoute le '/' entre le chemin et la commande                          */
/*   2. Vérifie si la commande existe et est exécutable                       */
/*   3. Tente chaque chemin jusqu'à trouver une commande valide               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : nom de la commande à chercher                                    */
/*   - paths : tableau de chemins où chercher la commande                     */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Le chemin complet de la commande si trouvée                            */
/*   - NULL si la commande n'est pas trouvée                                  */
/*                                                                            */
/* ************************************************************************** */
static char	*get_cmd_path(char *cmd, char **paths)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction principale de recherche de chemin d'une commande.               */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Vérifie si la commande est valide                                     */
/*   2. Si la commande contient '/', vérifie directement son accessibilité    */
/*   3. Recherche la variable PATH dans l'environnement                       */
/*   4. Décompose PATH et cherche la commande dans chaque répertoire          */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : nom de la commande à chercher                                    */
/*   - env : variables d'environnement                                        */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Le chemin complet de la commande si trouvée                            */
/*   - NULL si la commande n'est pas trouvée ou invalide                      */
/*                                                                            */
/* ************************************************************************** */
char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	path = get_cmd_path(cmd, paths);
	ft_free_split(paths, 0);
	return (path);
}
