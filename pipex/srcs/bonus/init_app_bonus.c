/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:42:24 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 14:47:26 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	create_pipes(t_pipex *data);
static void	init_pipe_fds(t_pipex *data);
static void	init_cpids(t_pipex *data);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'initialisation principale de l'application.                   */
/*                                                                            */
/*   Cette fonction initialise toutes les données nécessaires au programme :  */
/*   1. Configure les variables d'environnement                               */
/*   2. Calcule le nombre de commandes à exécuter                             */
/*   3. Initialise les descripteurs de fichiers                               */
/*   4. Crée les pipes nécessaires                                            */
/*   5. Ouvre les fichiers d'entrée/sortie                                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - ac : nombre d'arguments                                                */
/*   - av : tableau des arguments                                             */
/*   - env : variables d'environnement                                        */
/*                                                                            */
/* ************************************************************************** */
void	init_app(t_pipex *data, int ac, char **av, char **env)
{
	data->env = env;
	data->cmd_count = (ac - 3) - data->here_doc;
	data->infile = -1;
	data->outfile = -1;
	init_pipe_fds(data);
	init_cpids(data);
	create_pipes(data);
	open_files(data, ac, av);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de création des pipes pour la communication inter-processus.    */
/*                                                                            */
/*   Cette fonction crée les pipes nécessaires entre les commandes :          */
/*   1. Itère sur le nombre de commandes moins 1                              */
/*   2. Crée un pipe pour chaque paire de commandes adjacentes                */
/*   3. Gère les erreurs potentielles de création de pipe                     */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*                                                                            */
/* ************************************************************************** */
static void	create_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < (data->cmd_count - 1))
	{
		if (pipe(data->pipe_fds[i]) < 0)
			ft_exit("Pipe error", data);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'initialisation des descripteurs de fichiers pour les pipes.   */
/*                                                                            */
/*   Cette fonction alloue la mémoire pour les descripteurs de fichiers :     */
/*   1. Alloue le tableau principal de pointeurs                              */
/*   2. Alloue chaque tableau de deux entiers pour chaque pipe                */
/*   3. Gère les erreurs d'allocation avec libération propre                  */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*                                                                            */
/* ************************************************************************** */
static void	init_pipe_fds(t_pipex *data)
{
	int	i;

	data->pipe_fds = malloc(sizeof(int *) * (data->cmd_count - 1));
	if (!data->pipe_fds)
		ft_exit("Error: Malloc", data);
	i = 0;
	while (i < data->cmd_count - 1)
	{
		data->pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!data->pipe_fds[i])
		{
			free_pipe_fds(data->pipe_fds, i);
			ft_exit("Error: Malloc", data);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'initialisation des PIDs des processus enfants.                */
/*                                                                            */
/*   Cette fonction alloue la mémoire pour stocker les PIDs :                 */
/*   1. Alloue un tableau de taille cmd_count                                 */
/*   2. Gère les erreurs d'allocation avec libération des ressources          */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*                                                                            */
/* ************************************************************************** */
static void	init_cpids(t_pipex *data)
{
	data->cpids = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->cpids)
	{
		free_pipe_fds(data->pipe_fds, data->cmd_count - 1);
		ft_exit("Error: Malloc", data);
	}
}
