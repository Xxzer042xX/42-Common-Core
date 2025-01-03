/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:37:05 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/03 22:37:05 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* src/core/multi_pipe_bonus.c */
#include "../../include/pipex.h"

void	execute_pipex_bonus(t_pipex *pipex)
{
	int	i;

	create_pipes(pipex);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmds[i].pid = fork();
		if (pipex->cmds[i].pid == -1)
			error_exit(ERR_FORK);
		if (pipex->cmds[i].pid == 0)
		{
			redirect_io(&pipex, &pipex.cmds[i], i);
			execute_cmd(&pipex.cmds[i], pipex->env);
		}
		i++;
	}
	close_pipes(pipex);
	while (wait(NULL) > 0)
		;
}

