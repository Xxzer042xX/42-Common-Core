/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:49:06 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/11 14:34:12 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	execute_cmd(t_pipex *data, char *cmd, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		ft_exit("Error: Split failed", data);
	path = find_path(args[0], env);
	if (!path)
	{
		ft_free_split(args, 0);
		ft_exit("Error: Command not found", data);
	}
	if (execve(path, args, env) == -1)
	{
		free(path);
		ft_free_split(args, 0);
		ft_exit("Error: Execve failed", data);
	}
}
