/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:48:53 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 14:18:07 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"
#include <stdio.h>
#include <stdlib.h>

static void	close_fd(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
			perror("Warning: Close failed");
	}
}

static void	first_child(t_pipex *data)
{
	close(data->pipe_fd[0]);
	if (dup2(data->infile, STDIN_FILENO) == -1)
	{
		perror(">Error: Dup2 failed for infile");
		exit(EXIT_FAILURE);
	}
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error: Dup2 failed");
		exit(EXIT_FAILURE);
	}
	close_fd(data->pipe_fd[1]);
	close_fd(data->infile);
	close_fd(data->outfile);
	execute_cmd(data->cmd1, data->env);
}

static void	second_child(t_pipex *data)
{
	close_fd(data->pipe_fd[1]);
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("Error: Dup2 failed for pipe");
		exit(EXIT_FAILURE);
	}
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
	{
		perror("Error: Dup2 failed for outfile");
		exit(EXIT_FAILURE);
	}
	close_fd(data->pipe_fd[0]);
	close_fd(data->infile);
	close_fd(data->outfile);
	execute_cmd(data->cmd2, data->env);
}

void	create_process(t_pipex *data)
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
	close_fd(data->pipe_fd[0]);
	close_fd(data->pipe_fd[1]);
	close_fd(data->infile);
	close_fd(data->outfile);
}
