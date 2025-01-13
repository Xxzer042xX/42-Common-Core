/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:01:01 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 15:00:48 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

/* ************************************************************************** */
/*                              OWN LIB                                       */
/* ************************************************************************** */
# include "../lib/libftprintf/include/ft_printf.h"
# include "../lib/libftprintf/libft/libft.h"

typedef struct s_pipex
{
	pid_t	*cpids;
	char	**env;
	char	**cmds;
	char	*limiter;
	int		**pipe_fds;
	int		cmd_count;
	int		pipe_count;
	int		infile;
	int		outfile;
	int		here_doc;
}	t_pipex;

void	init_app(t_pipex *data, int ac, char **av, char **env);

void	create_processes(t_pipex *data, char **av);

void	close_all_pipes(t_pipex *data);

void	open_files(t_pipex *data, int ac, char **av);

void	close_fd(int fd);

void	handle_heredoc(t_pipex *data);

void	execute_cmd(t_pipex *data, char *cmd, char **env);

void	wait_processes(t_pipex *data);

void	free_parent(t_pipex *data);

void	free_pipe_fds(int **pipe_fds, int i);

void	ft_exit(char *str, t_pipex *data);

void	print_error_args(void);

char	*find_path(char *cmd, char **env);

#endif
