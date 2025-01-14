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


/* ************************************************************************** */
/*                                                                            */
/*   Fonction principale de gestion du heredoc.                               */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Crée un fichier temporaire                                            */
/*   2. Gère la lecture des entrées                                           */
/*   3. Configure le fichier d'entrée pour le pipeline                        */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*                                                                            */
/* ************************************************************************** */
void	handle_heredoc(t_pipex *data)
{
	int		temp_fd;

	temp_fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp_fd < 0)
		ft_exit("Heredoc temp file error", data);
	read_heredoc_input(data, temp_fd);
	close(temp_fd);
	data->infile = open(".heredoc_tmp", O_RDONLY);
	if (data->infile < 0)
	{
		unlink(".heredoc_tmp");
		ft_exit("Heredoc file error", data);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de lecture des entrées pour le heredoc.                         */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Lit les entrées standard jusqu'au délimiteur                          */
/*   2. Écrit chaque ligne dans le fichier temporaire                         */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - data : structure contenant les données du programme                    */
/*   - temp_fd : descripteur du fichier temporaire                            */
/*                                                                            */
/* ************************************************************************** */
static void	read_heredoc_input(t_pipex *data, int temp_fd)
{
	char	*line;

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
}
