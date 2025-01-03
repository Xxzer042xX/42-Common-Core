/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:55:47 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/03 20:55:47 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* src/core/cmd_utils.c */
#include "../../include/pipex.h"

static char	*get_cmd_path(char *cmd, char **paths)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	path = get_cmd_path(cmd, paths);
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (path);
}

void	execute_cmd(t_cmd *cmd, char **env)
{
	execve(cmd->path, cmd->args, env);
	perror("execve");
	exit(127);
}

void	parse_cmd(t_cmd *cmd, char *arg, char **env)
{
	cmd->args = ft_split(arg, ' ');
	if (!cmd->args)
		error_exit("malloc");
	cmd->path = find_path(cmd->args[0], env);
	if (!cmd->path)
	{
		if (access(cmd->args[0], X_OK) == 0)
			cmd->path = ft_strdup(cmd->args[0]);
		else
			cmd_error_exit(cmd->args[0]);
	}
}
