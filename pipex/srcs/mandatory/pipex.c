/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:05:42 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/03 20:05:42 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	init_pipex(t_pipex *pipex, int argc, char **argv, char **env);
static void	free_pipex(t_pipex *pipex);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		i;

	if (argc != 5)
		error_exit(ERR_INPUT);
	init_pipex(&pipex, argc, argv, env);
	create_pipes(&pipex);
	i = 0;
	while (i < pipex.cmd_count)
	{
		pipex.cmds[i].pid = fork();
		if (pipex.cmds[i].pid == -1)
			error_exit(ERR_FORK);
		if (pipex.cmds[i].pid == 0)
		{
			redirect_io(&pipex, &pipex.cmds[i], i);
			execute_cmd(&pipex.cmds[i], env);
		}
	}
	close_pipes(&pipex);
	while (wait(NULL) > 0)
		;
	free_pipex(&pipex);
	return (0);
}

static void	init_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	int	i;

	pipex->cmd_count = argc - 3;
	pipex->env = env;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->cmds = malloc(sizeof(t_cmd) * pipex->cmd_count);
	if (!pipex->cmds)
		error_exit("malloc");
	i = -1;
	while (++i < pipex->cmd_count)
	{
		pipex->cmds[i].args = NULL;
		pipex->cmds[i].path = NULL;
		pipex->cmds[i].pid = -1;
	}
	i = -1;
	while (++i < pipex->cmd_count)
		parse_cmd(&pipex->cmds[i], argv[i + 2], env);
	open_files(pipex, argv, argc);
}

static void	free_pipex(t_pipex *pipex)
{
	int	i;
	int	j;

	if (pipex->cmds)
	{
		i = -1;
		while (++i < pipex->cmd_count)
		{
			if (pipex->cmds[i].args)
			{
				j = -1;
				while (pipex->cmds[i].args[++j])
					free(pipex->cmds[i].args[j]);
				free(pipex->cmds[i].args);
			}
			if (pipex->cmds[i].path)
				free(pipex->cmds[i].path);
		}
		free(pipex->cmds);
	}
	close_files(pipex);
}
