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

static void	init_app(t_pipex *data, int ac, char **av, char **env)
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
	open_files(data, ac, av);
	print_status_init(data);
}

static void	open_files(t_pipex *data, int ac, char **av)
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

static void	print_status_init(t_pipex *data)
{
	ft_printf("Initialisation des données:\n");
	ft_printf("commandes reçues\t n1: %s\t", data->cmd1);
	ft_printf("n2: %s\n", data->cmd2);
	ft_printf("Fichiers reçus\t\t f1: %s\t", data->env[0]);
	ft_printf("f2: %s\n", data->env[1]);
	ft_printf("Pipe créé: [%d, %d]\n", data->pipe_fd[0], data->pipe_fd[1]);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	data;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	init_app(&data, ac, av, env);
	creat_process(&data);
    ft_printf("En attente des processus %d et %d\n", data.cpid1, data.cpid2);
	waitpid(data.cpid1, NULL, 0);
	waitpid(data.cpid2, NULL, 0);
	return (0);
}
