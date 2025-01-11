/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:49:16 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/11 02:49:16 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char *get_path_from_env(char **env)
{
    while (*env)
    {
        if (ft_strncmp(*env, "PATH=", 5) == 0)
            return (*env + 5);
        env++;
    }
    return (NULL);
}

char    *find_path(char *cmd, char **env)
{
    char **paths;
    char *path;
    char *part_path;
    int i;

    path = get_path_from_env(env);
    if (!path)
        return (NULL);
    paths = ft_split(path, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK) == 0)
        {
            ft_printf("Command found at: %s\n", path);
            return (path);
        }
        free(path);
        i++;
    }
    return (NULL);
}
