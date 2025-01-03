/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:55:56 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/03 20:55:56 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* src/core/file_utils.c */
#include "../../include/pipex.h"

void	open_files(t_pipex *pipex, char **argv, int argc)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		perror(ERR_INFILE);
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		error_exit(ERR_OUTFILE);
}

void	close_files(t_pipex *pipex)
{
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
}
