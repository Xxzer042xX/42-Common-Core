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
