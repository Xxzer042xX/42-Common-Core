/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:48:53 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 14:18:07 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	child_process(t_pipex *data, char **av, int i);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de création des processus enfants.                              */
/*                                                                            */
/*   Cette fonction gère la création de tous les processus nécessaires :      */
/*   1. Crée un processus enfant pour chaque commande                         */
/*   2. Vérifie les erreurs de fork pour chaque création                      */
/*   3. Lance le processus enfant avec la configuration appropriée            */
/*   4. Ferme les pipes et fichiers dans le processus parent                  */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - av : tableau des arguments du programme                                */
/*                                                                            */
/* ************************************************************************** */
void	create_processes(t_pipex *data, char **av)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		data->cpids[i] = fork();
		if (data->cpids[i] == -1)
			ft_exit("Fork error", data);
		if (data->cpids[i] == 0)
			child_process(data, av, i);
		i++;
	}
	close_all_pipes(data);
	close_fd(data->infile);
	close_fd(data->outfile);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'attente de la fin des processus enfants.                      */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Attend la terminaison de chaque processus enfant                      */
/*   2. Collecte le statut de sortie de chaque processus                      */
/*   3. Évite les processus zombies                                           */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*                                                                            */
/* ************************************************************************** */
int	wait_processes(t_pipex *data)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < data->cmd_count)
	{
		waitpid(data->cpids[i], &status, 0);
		if (i == data->cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
		}
		i++;
	}
	return (last_status);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de configuration et exécution du processus enfant.              */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Détermine le type de processus (premier, dernier, intermédiaire)      */
/*   2. Configure les redirections appropriées                                */
/*   3. Ferme tous les descripteurs de fichiers non nécessaires               */
/*   4. Exécute la commande                                                   */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - av : tableau des arguments du programme                                */
/*   - i : index du processus courant                                         */
/*                                                                            */
/* ************************************************************************** */
static void	child_process(t_pipex *data, char **av, int i)
{
	if (i == 0)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
			ft_exit("Error: Dup2 failed for infile", data);
		if (dup2(data->pipe_fds[0][1], STDOUT_FILENO) == -1)
			ft_exit("Error: Dup2 failed for pipe", data);
	}
	else if (i == data->cmd_count - 1)
	{
		if (dup2(data->pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			ft_exit("Error: Dup2 failed for pipe", data);
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			ft_exit("Error: Dup2 failed for outfile", data);
	}
	else
	{
		if (dup2(data->pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			ft_exit("Error: Dup2 failed for pipe", data);
		if (dup2(data->pipe_fds[i][1], STDOUT_FILENO) == -1)
			ft_exit("Error: Dup2 failed for pipe", data);
	}
	close_all_pipes(data);
	close_fd(data->infile);
	close_fd(data->outfile);
	execute_cmd(data, av[(i + 2) + data->here_doc], data->env);
}
