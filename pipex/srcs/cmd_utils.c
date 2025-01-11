/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:49:06 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/11 02:49:06 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_cmd(char *cmd, char **env)
{
	char	*path;
	char 	**args;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		ft_putstr_fd("Error: Split failed", 2);
		exit(EXIT_FAILURE);
	}
	path = find_path(cmd, env);
	if (path)
	{
		execve(path, args, env);
		perror("Error: Execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd("Error: Command not found\n", 2);
		exit(EXIT_FAILURE);
	}
}