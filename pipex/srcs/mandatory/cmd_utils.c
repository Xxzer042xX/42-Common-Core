/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:49:06 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/11 14:34:12 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	execute_cmd(char *cmd, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		ft_putstr_fd("Error: Split failed", 2);
		exit(EXIT_FAILURE);
	}
	path = find_path(args[0], env);
	if (!path)
	{
		ft_printf("Error: Command '%s' not found\n", args[0]);
		ft_free_split(args, 0);
		exit(EXIT_FAILURE);
	}
	if (execve(path, args, env) == -1)
	{
		perror("Error: Execve failed");
		free(path);
		ft_free_split(args, 0);
		exit(EXIT_FAILURE);
	}
}
