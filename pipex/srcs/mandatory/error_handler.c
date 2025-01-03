/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:56:09 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/03 20:56:09 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	error_exit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

void	cmd_error_exit(char *cmd)
{
	ft_putstr_fd(ERR_CMD, 2);
	ft_putendl_fd(cmd, 2);
	exit(127);
}
