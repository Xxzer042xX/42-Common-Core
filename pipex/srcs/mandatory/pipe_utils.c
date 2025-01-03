/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:55:51 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/03 20:55:51 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* src/core/pipe_utils.c */
#include "../../include/pipex.h"

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->cmds[i].pipe) == -1)
			error_exit(ERR_PIPE);
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_count - 1)
	{
		close(pipex->cmds[i].pipe[0]);
		close(pipex->cmds[i].pipe[1]);
	}
}

void	redirect_io(t_pipex *pipex, t_cmd *cmd, int i)
{
	if (i == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(cmd->pipe[1], STDOUT_FILENO);
	}
	else if (i == pipex->cmd_count - 1)
	{
		dup2(pipex->cmds[i - 1].pipe[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(pipex->cmds[i - 1].pipe[0], STDIN_FILENO);
		dup2(cmd->pipe[1], STDOUT_FILENO);
	}
	close_pipes(pipex);
}
