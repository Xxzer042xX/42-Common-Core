/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_util.c                                        :+:      :+:    :+:   */
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
/*   Fonction de test des chemins possibles pour une commande.                */
/*                                                                            */
/*   Pour chaque chemin dans PATH, cette fonction :                           */
/*   1. Construit le chemin complet :                                         */
/*      - Ajoute '/' entre le chemin et la commande                           */
/*      Ex: "/bin" + "/" + "ls" -> "/bin/ls"                                  */
/*                                                                            */
/*   2. Vérifie l'accessibilité :                                             */
/*      - F_OK : existence du fichier                                         */
/*      - X_OK : permission d'exécution                                       */
/*                                                                            */
/*   3. Gestion mémoire :                                                     */
/*      - Libère les chemins temporaires si non valides                       */
/*      - Retourne le premier chemin valide trouvé                            */
/*                                                                            */
/*   Exemple de recherche pour "ls" :                                         */
/*   1. Teste "/bin/ls"                                                       */
/*   2. Si échec, teste "/usr/bin/ls"                                         */
/*   3. Continue jusqu'à trouver un chemin valide                             */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : nom de la commande (ex: "ls")                                    */
/*   - paths : tableau de chemins du PATH (ex: ["/bin", "/usr/bin", ...])     */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Chemin valide (ex: "/bin/ls")                                          */
/*   - NULL si aucun chemin valide trouvé                                     */
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
/*   Fonction principale de résolution du chemin d'une commande.              */
/*                                                                            */
/*   Processus de recherche :                                                 */
/*   1. Vérifications initiales :                                             */
/*      - Commande non vide                                                   */
/*      - Si commande contient '/', vérifie directement le chemin             */
/*      Ex: "./script.sh" ou "/bin/ls"                                        */
/*                                                                            */
/*   2. Recherche dans PATH :                                                 */
/*      - Trouve la variable PATH dans env                                    */
/*      - Découpe PATH en tableau de chemins                                  */
/*      Ex: PATH=/bin:/usr/bin -> ["/bin", "/usr/bin"]                        */
/*                                                                            */
/*   3. Recherche dans chaque chemin via get_cmd_path                         */
/*      - Teste chaque chemin possible                                        */
/*      - Libère la mémoire du tableau de chemins                             */
/*                                                                            */
/*   Cas spéciaux :                                                           */
/*   - Commande avec chemin : "./cmd" ou "/path/to/cmd"                       */
/*   - Commande simple : "ls" ou "grep"                                       */
/*   - PATH non trouvé dans env                                               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - cmd : commande à chercher                                              */
/*   - env : variables d'environnement                                        */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Chemin complet de la commande                                          */
/*   - NULL si commande invalide ou introuvable                               */
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
	ft_free_split(paths);
	return (path);
}
