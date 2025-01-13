/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:48:53 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 14:18:07 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

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
}

void	wait_processes(t_pipex *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->cmd_count)
	{
		waitpid(data->cpids[i], &status, 0);
		i++;
	}
}

