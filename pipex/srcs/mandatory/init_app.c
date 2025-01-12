/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:42:24 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 14:47:26 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	open_files(t_pipex *data, char **av);
static void	check_files_access(char **av);

void	init_app(t_pipex *data, char **av, char **env)
{
	ft_memset(data, 0, sizeof(t_pipex));
	data->env = env;
	data->cmd1 = av[2];
	data->cmd2 = av[3];
	if (pipe(data->pipe_fd) == -1)
	{
		perror("Error: Pipe failed");
		exit(EXIT_FAILURE);
	}
	open_files(data, av);
}

static void	open_files(t_pipex *data, char **av)
{
	check_files_access(av);
	data->infile = open(av[1], O_RDONLY);
	if (data->infile == -1)
	{
		perror("Error: Input file permission denied");
		exit(EXIT_FAILURE);
	}
	data->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
	{
		perror("Error: Output file permission denied");
		exit(EXIT_FAILURE);
	}
}

static void	check_files_access(char **av)
{
	if (access(av[1], F_OK) == -1)
	{
		perror("Error: Input file does not exist");
		exit(EXIT_FAILURE);
	}
	if (access(av[1], R_OK) == -1)
	{
		perror("Error: Input file permission denied");
		exit(EXIT_FAILURE);
	}
	if (access(av[4], F_OK) == -1 && access(av[4], W_OK) == -1)
	{
		perror("Error: Output file permission denied");
		exit(EXIT_FAILURE);
	}
}
