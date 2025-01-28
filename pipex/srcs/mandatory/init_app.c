/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:29:56 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/15 10:48:20 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	create_pipes(t_pipex *data);
static void	init_pipe_fds(t_pipex *data);
static void	init_cpids(t_pipex *data);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'initialisation principale de l'application.                   */
/*                                                                            */
/*   Architecture du programme :                                              */
/*   Pour N commandes, le programme crée :                                    */
/*   - N-1 pipes pour connecter les commandes                                 */
/*   - N processus enfants (un pour chaque commande)                          */
/*   - 2 fichiers (entrée et sortie)                                          */
/*                                                                            */
/*   Étapes d'initialisation :                                                */
/*   1. Configuration de l'environnement et calcul des dimensions             */
/*      - Stockage des variables d'environnement                              */
/*      - Calcul du nombre de commandes (ac-3 ou ac-4 pour here_doc)          */
/*   2. Initialisation des structures                                         */
/*      - Tableau de pipes (pipe_fds[N-1][2])                                 */
/*      - Tableau de PIDs (cpids[N])                                          */
/*      - Descripteurs de fichiers (infile, outfile)                          */
/*   3. Création des pipes et ouverture des fichiers                          */
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
/*   Fonction d'initialisation des descripteurs de fichiers pour les pipes.   */
/*                                                                            */
/*   Structure des pipes :                                                    */
/*   pipe_fds est un tableau de N-1 pipes, où N est le nombre de commandes    */
/*   Chaque pipe[i] contient deux descripteurs de fichiers :                  */
/*   - pipe[i][0] : extrémité de lecture                                      */
/*   - pipe[i][1] : extrémité d'écriture                                      */
/*                                                                            */
/*   Exemple pour 3 commandes (cmd1 | cmd2 | cmd3) :                          */
/*   - pipe_fds[0] connecte cmd1 à cmd2                                       */
/*   - pipe_fds[1] connecte cmd2 à cmd3                                       */
/*                                                                            */
/*   Gestion d'erreurs :                                                      */
/*   En cas d'échec d'allocation :                                            */
/*   1. Libère toute la mémoire déjà allouée                                  */
/*   2. Termine le programme avec ERR_MALLOC                                  */
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
		ft_exit("Memory allocation failed", data, ERR_MALLOC);
	i = 0;
	while (i < (data->cmd_count - 1))
	{
		data->pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!data->pipe_fds[i])
		{
			free_pipe_fds(data->pipe_fds, i);
			ft_exit("Memory allocation failed", data, ERR_MALLOC);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de création des pipes pour la communication inter-processus.    */
/*                                                                            */
/*   Création du pipeline de commandes :                                      */
/*   Pour N commandes, crée N-1 pipes formant une chaîne :                    */
/*   cmd1 --> pipe[0] --> cmd2 --> pipe[1] --> cmd3 ... cmdN                  */
/*                                                                            */
/*   Flux de données :                                                        */
/*   1. La sortie de chaque commande i est connectée à pipe[i][1]             */
/*   2. L'entrée de chaque commande i+1 est connectée à pipe[i][0]            */
/*   3. Le premier processus lit depuis infile                                */
/*   4. Le dernier processus écrit dans outfile                               */
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
		if (pipe(data->pipe_fds[i]) == -1)
			ft_exit("Pipe error", data, ERR_PIPE);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'initialisation des PIDs des processus enfants.                */
/*                                                                            */
/*   Rôle dans l'architecture :                                               */
/*   - Alloue un tableau pour stocker les PIDs de tous les processus          */
/*   - Permet de suivre et gérer tous les processus enfants                   */
/*                                                                            */
/*   Structure :                                                              */
/*   - cpids[i] stocke le PID du processus exécutant la commande i            */
/*   - La taille du tableau est égale au nombre de commandes                  */
/*   Exemple pour "cmd1 | cmd2 | cmd3" :                                      */
/*   - cpids[0] = PID du processus exécutant cmd1                             */
/*   - cpids[1] = PID du processus exécutant cmd2                             */
/*   - cpids[2] = PID du processus exécutant cmd3                             */
/*                                                                            */
/*   Gestion d'erreurs :                                                      */
/*   1. En cas d'échec d'allocation :                                         */
/*      - Libère les pipes déjà alloués                                       */
/*      - Termine le programme avec ERR_MALLOC                                */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*                                                                            */
/*   Note : Ce tableau est essentiel pour wait_processes qui l'utilise        */
/*   pour attendre la fin de tous les processus enfants.                      */
/*                                                                            */
/* ************************************************************************** */
static void	init_cpids(t_pipex *data)
{
	data->cpids = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->cpids)
	{
		free_pipe_fds(data->pipe_fds, data->cmd_count - 1);
		ft_exit("Memory allocation failed", data, ERR_MALLOC);
	}
}
