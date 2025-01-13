/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:04:50 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/13 10:04:50 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	handle_heredoc(t_pipex *data)
{
	char	*line;
	int		temp_fd;

	temp_fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp_fd < 0)
		ft_exit("Heredoc temp file error", data);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, data->limiter, ft_strlen(data->limiter)) && \
			line[ft_strlen(data->limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(temp_fd, line, ft_strlen(line));
		free(line);
	}
	close(temp_fd);
	data->infile = open(".heredoc_tmp", O_RDONLY);
	if (data->infile < 0)
	{
		unlink(".heredoc_tmp");
		ft_exit("Heredoc file error", data);
	}
}
