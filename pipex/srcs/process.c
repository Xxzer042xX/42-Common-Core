/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:48:53 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/11 02:48:53 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	close_data(t_pipex *data)
{
	if (close(data->pipe_fd[0]) == -1 || close(data->pipe_fd[1]) == -1 || \
		close(data->infile) == -1 || close(data->outfile) == -1)
	{
		perror("Error: Close failed");
		exit(EXIT_FAILURE);
	}
}

static void	first_child(t_pipex *data)
{
	if (dup2(data->infile, STDIN_FILENO) == -1 || \
		dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error: Dup2 failed");
		exit(EXIT_FAILURE);
	}
	close_data(data);
	execute_cmd(data->cmd1, data->env);
}

static void	second_child(t_pipex *data)
{
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1 || \
		dup2(data->outfile, STDOUT_FILENO) == -1)
	{
		perror("Error: Dup2 failed");
		exit(EXIT_FAILURE);
	}
	close_data(data);
	execute_cmd(data->cmd2, data->env);
}

void	creat_process(t_pipex *data)
{
	data->cpid1 = fork();
	if (data->cpid1 == -1)
	{
		perror("Error: Fork failed");
		exit(EXIT_FAILURE);
	}
	if (data->cpid1 == 0)
		first_child(data);
	data->cpid2 = fork();
	if (data->cpid2 == -1)
	{
		perror("Error: Fork failed");
		exit(EXIT_FAILURE);
	}
	if (data->cpid2 == 0)
		second_child(data);
	close_data(data->pipe_fd[0]);
	close_data(data->pipe_fd[1]);
}
