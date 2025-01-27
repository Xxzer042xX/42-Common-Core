/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:16:18 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/13 12:16:18 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de fermeture sécurisée d'un descripteur de fichier.             */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Vérifie si le descripteur est valide (-1 = invalide)                  */
/*   2. Tente de fermer le descripteur                                        */
/*   3. Affiche un avertissement en cas d'échec                               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - fd : descripteur de fichier à fermer                                   */
/*                                                                            */
/* ************************************************************************** */
void	close_fd(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
			perror("Warning: Close failed");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de sortie propre du programme avec message d'erreur.            */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Libère la mémoire si une structure data est fournie                   */
/*   2. Affiche le message d'erreur avec perror                               */
/*   3. Termine le programme avec EXIT_FAILURE                                */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - str : message d'erreur à afficher                                      */
/*   - data : structure à libérer (peut être NULL)                            */
/*                                                                            */
/* ************************************************************************** */
void	ft_exit(char *str, t_pipex *data, int status)
{
	if (data)
		free_parent(data);
	perror(str);
	exit(status);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de libération complète de la mémoire du processus parent.       */
/*                                                                            */
/*   Cette fonction libère :                                                  */
/*   1. Les tableaux de descripteurs de pipes                                 */
/*   2. Le tableau des PIDs des processus enfants                             */
/*   3. Le fichier temporaire heredoc si utilisé                              */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données à libérer                       */
/*                                                                            */
/* ************************************************************************** */
void	free_parent(t_pipex *data)
{
	int	i;

	if (data->pipe_fds)
	{
		i = 0;
		while (i < data->cmd_count - 1)
		{
			if (data->pipe_fds[i])
				free(data->pipe_fds[i]);
			i++;
		}
		free(data->pipe_fds);
		data->pipe_fds = NULL;
	}
	if (data->cpids)
	{
		free(data->cpids);
		data->cpids = NULL;
	}
	if (data->here_doc)
		unlink(".heredoc_tmp");
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de fermeture de tous les pipes du programme.                    */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Parcourt tous les pipes créés                                         */
/*   2. Ferme les extrémités lecture et écriture de chaque pipe               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les pipes à fermer                          */
/*                                                                            */
/* ************************************************************************** */
void	close_all_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		close(data->pipe_fds[i][0]);
		close(data->pipe_fds[i][1]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de libération des tableaux de descripteurs de pipes.            */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Libère chaque sous-tableau de descripteurs                            */
/*   2. Met les pointeurs à NULL après libération                             */
/*   3. Libère le tableau principal                                           */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - pipe_fds : tableau de tableaux de descripteurs à libérer               */
/*   - i : index jusqu'où libérer                                             */
/*                                                                            */
/* ************************************************************************** */
void	free_pipe_fds(int **pipe_fds, int i)
{
	while (i >= 0)
	{
		if (pipe_fds[i])
		{
			free(pipe_fds[i]);
			pipe_fds[i] = NULL;
		}
		i--;
	}
	free(pipe_fds);
}
