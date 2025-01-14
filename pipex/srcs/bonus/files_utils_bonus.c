/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:33:46 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/13 12:33:46 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	check_files_access(t_pipex *data, char **av);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'ouverture des fichiers d'entrée et de sortie.                 */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Gère deux modes : heredoc et normal                                   */
/*   2. Pour le mode heredoc :                                                */
/*      - Configure l'entrée via handle_heredoc                               */
/*      - Ouvre le fichier de sortie en mode append                           */
/*   3. Pour le mode normal :                                                 */
/*      - Vérifie les permissions des fichiers                                */
/*      - Ouvre le fichier d'entrée en lecture                                */
/*      - Ouvre le fichier de sortie en écriture (truncate)                   */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - ac : nombre d'arguments                                                */
/*   - av : tableau des arguments du programme                                */
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
		if (data->infile < 0)
			ft_exit("Infile error", data);
		data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (data->outfile == -1)
		ft_exit("Outfile error", data);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de vérification des permissions des fichiers.                   */
/*                                                                            */
/*   Cette fonction vérifie :                                                 */
/*   1. L'existence du fichier d'entrée                                       */
/*   2. Les droits en lecture sur le fichier d'entrée                         */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - av : tableau des arguments du programme                                */
/*                                                                            */
/* ************************************************************************** */
static void	check_files_access(t_pipex *data, char **av)
{
	if (access(av[1], F_OK) == -1)
		ft_exit("Error: Input file does not exist", data);
	if (access(av[1], R_OK) == -1)
		ft_exit("Error: Input file permission denied", data);
}
