/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:37:26 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/03 22:37:26 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	write_heredoc(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 &&
			line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}

void	handle_heredoc(t_pipex *pipex, char **argv, int argc)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error_exit(ERR_PIPE);
	write_heredoc(fd[1], argv[2]);
	close(fd[1]);
	pipex->infile = fd[0];
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->outfile == -1)
		error_exit(ERR_OUTFILE);
}
