/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:29:21 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/14 12:29:24 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	check_files_access(t_pipex *data, char **av);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de gestion des fichiers d'entrée/sortie du pipeline.            */
/*                                                                            */
/*   Gère deux modes de fonctionnement :                                      */
/*   1. Mode heredoc (<<) :                                                   */
/*      - Entrée : créée par handle_heredoc                                   */
/*      - Sortie : mode append (>>)                                           */
/*      Exemple : cmd << DELIM >> outfile                                     */
/*                                                                            */
/*   2. Mode normal (< >) :                                                   */
/*      - Entrée : mode lecture seule                                         */
/*      - Sortie : truncate et création si nécessaire                         */
/*      Exemple : < infile cmd > outfile                                      */
/*                                                                            */
/*   Permissions des fichiers :                                               */
/*   - Fichiers créés : rw-r--r-- (0644)                                      */
/*   - Vérifie les droits en lecture pour infile                              */
/*   - Vérifie les droits en écriture pour outfile                            */
/*                                                                            */
/*   Gestion d'erreurs :                                                      */
/*   - Échec d'ouverture outfile -> ERR_NO_SUCH_FILE                          */
/*   - Autres erreurs gérées par check_files_access                           */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - ac : nombre d'arguments                                                */
/*   - av : tableau des arguments                                             */
/*                                                                            */
/* ************************************************************************** */
void	open_files(t_pipex *data, int ac, char **av)
{
	if (data->here_doc)
	{
		handle_heredoc(data);
		data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		check_files_access(data, av);
		data->infile = open(av[1], O_RDONLY);
		data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (data->outfile == -1)
		ft_exit("no create outfile", data, ERR_NO_SUCH_FILE);
}

/* ************************************************************************** */
/*                                                                            */
/*   check_files_access:                                                      */
/*   Fonction de vérification des permissions des fichiers.                   */
/*                                                                            */
/*   Cette fonction vérifie deux conditions pour le fichier d'entrée :        */
/*   1. Existence du fichier (F_OK)                                           */
/*      - Si n'existe pas -> ERR_NO_SUCH_FILE                                 */
/*      - Message: "bash: infile: No such file or directory"                  */
/*                                                                            */
/*   2. Permissions en lecture (R_OK)                                         */
/*      - Si pas de permission -> ERR_PERMISSION                              */
/*      - Message: "input file permission denied"                             */
/*                                                                            */
/*   Note : Cette vérification n'est pas faite en mode heredoc                */
/*   car le fichier d'entrée est créé temporairement par le programme.        */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - av : tableau des arguments (av[1] est le fichier d'entrée)             */
/*                                                                            */
/* ************************************************************************** */
static void	check_files_access(t_pipex *data, char **av)
{
	if (access(av[1], F_OK) == -1)
		ft_exit("bash: infile: ", data, ERR_NO_SUCH_FILE);
	if (access(av[1], R_OK) == -1)
		ft_exit("input file permission denied", data, ERR_PERMISSION);
}
