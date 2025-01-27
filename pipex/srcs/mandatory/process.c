/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:48:53 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/15 11:28:42 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	child_process(t_pipex *data, char **av, int i);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de création des processus enfants.                              */
/*                                                                            */
/*   Architecture du pipeline :                                               */
/*   Pour N commandes, crée N processus enfants connectés par N-1 pipes       */
/*   Exemple avec 3 commandes : cmd1 | cmd2 | cmd3                            */
/*      fork1 --> exécute cmd1, écrit dans pipe[0]                            */
/*      fork2 --> lit pipe[0], exécute cmd2, écrit dans pipe[1]               */
/*      fork3 --> lit pipe[1], exécute cmd3                                   */
/*                                                                            */
/*   Processus de création :                                                  */
/*   1. Pour chaque commande i (0 à N-1) :                                    */
/*      - fork() crée un nouveau processus                                    */
/*      - Le processus enfant exécute child_process(i)                        */
/*      - Le parent continue la boucle                                        */
/*   2. Après création de tous les processus :                                */
/*      - Fermeture de tous les pipes dans le parent                          */
/*      - Fermeture des fichiers d'entrée/sortie                              */
/*                                                                            */
/*   Gestion d'erreurs :                                                      */
/*   - Vérifie chaque fork()                                                  */
/*   - En cas d'échec, termine avec ERR_FORK                                  */
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
		{
			perror("Error: Fork failed");
			exit(ERR_FORK);
		}
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
/*   Fonction de configuration et exécution du processus enfant.              */
/*                                                                            */
/*   Configuration des redirections selon la position :                       */
/*   1. Premier processus (i == 0) :                                          */
/*      - Entrée : fichier d'entrée (infile)                                  */
/*      - Sortie : pipe[0] pour écrire vers cmd2                              */
/*                                                                            */
/*   2. Processus intermédiaires (0 < i < N-1) :                              */
/*      - Entrée : pipe[i-1] pour lire depuis cmdi-1                          */
/*      - Sortie : pipe[i] pour écrire vers cmdi+1                            */
/*                                                                            */
/*   3. Dernier processus (i == N-1) :                                        */
/*      - Entrée : pipe[N-2] pour lire depuis cmdN-1                          */
/*      - Sortie : fichier de sortie (outfile)                                */
/*                                                                            */
/*   Séquence d'exécution :                                                   */
/*   1. Configuration des redirections avec dup2                              */
/*   2. Fermeture de tous les descripteurs non nécessaires                    */
/*   3. Exécution de la commande                                              */
/*                                                                            */
/*   Gestion d'erreurs :                                                      */
/*   - Vérifie chaque dup2                                                    */
/*   - En cas d'échec, termine avec ERR_DUP                                   */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - av : tableau des arguments du programme                                */
/*   - i : index du processus (0 à N-1)                                       */
/*                                                                            */
/* ************************************************************************** */
static void	child_process(t_pipex *data, char **av, int i)
{
	if (i == 0)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
			ft_exit("Dup2 failed for infile", data, ERR_DUP);
		if (dup2(data->pipe_fds[0][1], STDOUT_FILENO) == -1)
			ft_exit("Dup2 failed for pipe", data, ERR_DUP);
	}
	else if (i == data->cmd_count - 1)
	{
		if (dup2(data->pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			ft_exit("Dup2 failed for pipe", data, ERR_DUP);
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			ft_exit("Dup2 failed for outfile", data, ERR_DUP);
	}
	else
	{
		if (dup2(data->pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			ft_exit("Dup2 failed for pipe", data, ERR_DUP);
		if (dup2(data->pipe_fds[i][1], STDOUT_FILENO) == -1)
			ft_exit("Dup2 failed for pipe", data, ERR_DUP);
	}
	close_all_pipes(data);
	close_fd(data->infile);
	close_fd(data->outfile);
	execute_cmd(data, av[(i + 2) + data->here_doc], data->env);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'attente de la fin des processus enfants.                      */
/*                                                                            */
/*   Processus d'attente :                                                    */
/*   1. Pour chaque processus enfant (i de 0 à N-1) :                         */
/*      - waitpid attend spécifiquement le PID stocké dans cpids[i]           */
/*      - Récupère le statut de sortie via WEXITSTATUS                        */
/*      - Si un processus échoue (statut != 0), retourne son statut           */
/*                                                                            */
/*   Comportement :                                                           */
/*   - Attend tous les processus dans l'ordre                                 */
/*   - Évite les processus zombies                                            */
/*   - Propage le premier statut d'erreur rencontré                           */
/*                                                                            */
/*   Retourne :                                                               */
/*   - 0 si tous les processus se terminent avec succès                       */
/*   - Code d'erreur du premier processus qui échoue                          */
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
		if (WIFEXITED(status))
		{
			last_status = WEXITSTATUS(status);
			if (last_status != 0)
				return (last_status);
		}
		i++;
	}
	return (last_status);
}
