/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:16:18 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/13 12:16:18 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	close_fd(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
			perror("Warning: Close failed");
	}
}

void	ft_exit(char *str, t_pipex *data)
{
	if (data)
		free_parent(data);
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_parent(t_pipex *data)
{
	int	i;

	close_fd(data->infile);
	close_fd(data->outfile);
	if (data->pipe_fds)
	{
		i = 0;
		while (i < data->cmd_count - 1)
		{
			if (data->pipe_fds[i])
			{
				close_fd(data->pipe_fds[i][0]);
				close_fd(data->pipe_fds[i][1]);
				free(data->pipe_fds[i]);
			}
			i++;
		}
		free(data->pipe_fds);
	}
	if (data->cpids)
		free(data->cpids);
	if (data->here_doc)
		unlink(".heredoc_tmp");
}

void	close_all_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		if (close(data->pipe_fds[i][0]) == -1)
			ft_exit("Error: Close failed", data);
		if (close(data->pipe_fds[i][1]) == -1)
			ft_exit("Error: Close failed", data);
		i++;
	}
}

void	free_pipe_fds(int **pipe_fds, int i)
{
	while (i >= 0)
	{
		if (pipe_fds[i])
			free(pipe_fds[i]);
		i--;
	}
	free(pipe_fds);
}
