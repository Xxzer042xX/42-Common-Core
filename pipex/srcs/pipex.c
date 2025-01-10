/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:46:48 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/10 20:48:56 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>

int	main(void)
{
	t_pipex	data;
	pid_t	cpid1;
	pid_t	cpid2;

	pipe(data.pipe_fd);
	cpid1 = fork();
	if (cpid1 == 0)
	{
		dup2(data.pipe_fd[1], STDOUT_FILENO);
		close(data.pipe_fd[0]);
		close(data.pipe_fd[1]);
        char *args[] = {"ls", "-la", NULL};
		execvp(const char *file, char *const *argv)
		perror("execvp ls");
		exit(EXIT_FAILURE);
	}
	cpid2 = fork();
	if (cpid2 == 0)
	{
		dup2(data.pipe_fd[0], STDIN_FILENO);
		close(data.pipe_fd[0]);
		close(data.pipe_fd[1]);
        char *args[] = {"sort", "-r", NULL};
		execve("sort", args);
		perror("execvp wc");
		exit(EXIT_FAILURE);
	}
	close(data.pipe_fd[0]);
	close(data.pipe_fd[1]);
	waitpid(cpid1, NULL, 0);
	waitpid(cpid2, NULL, 0);
	return (0);
}
