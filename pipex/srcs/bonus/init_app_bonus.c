/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:42:24 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 14:47:26 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	create_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < (data->cmd_count - 1))
	{
		if (pipe(data->pipe_fds[i]) < 0)
			ft_exit("Pipe error", data);
		i++;
	}
}

static void	init_pipe_fds(t_pipex *data)
{
	int	i;

	i = 0;
	data->pipe_fds = malloc(sizeof(int *) * (data->cmd_count - 1));
	if (!data->pipe_fds)
		ft_exit("Error: Malloc", data);
	i = 0;
	while (i < data->cmd_count - 1)
	{
		data->pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!data->pipe_fds[i])
		{
			free_pipe_fds(data->pipe_fds, i);
			ft_exit("Error: Malloc", data);
		}
		i++;
	}
}

static void	init_cpids(t_pipex *data)
{
	data->cpids = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->cpids)
	{
		free_pipe_fds(data->pipe_fds, data->cmd_count - 1);
		ft_exit("Error: Malloc", data);
	}
}

void	init_app(t_pipex *data, int ac, char **av, char **env)
{
	ft_memset(data, 0, sizeof(t_pipex));
	data->env = env;
	data->cmd_count = (ac - 3) - data->here_doc;
	init_pipe_fds(data);
	init_cpids(data);
	create_pipes(data);
	open_files(data, ac, av);
}
