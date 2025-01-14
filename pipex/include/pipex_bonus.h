/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:01:01 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 15:00:48 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* ************************************************************************** */
/*                              STANDARD LIB                                  */
/* ************************************************************************** */
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* ************************************************************************** */
/*                              OWN LIB                                       */
/* ************************************************************************** */
# include "../lib/libftprintf/include/ft_printf.h"
# include "../lib/libftprintf/libft/libft.h"

/* ************************************************************************** */
/*                              STRUCTUR PIPEX                                */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*                              CORE FUNCTIONS                                */
/* ************************************************************************** */
int		wait_processes(t_pipex *data);
void	init_app(t_pipex *data, int ac, char **av, char **env);
void	create_processes(t_pipex *data, char **av);

/* ************************************************************************** */
/*                              FILES FUNCTIONS                               */
/* ************************************************************************** */
void	open_files(t_pipex *data, int ac, char **av);

/* ************************************************************************** */
/*                              HEREDOC FUNCTIONS                             */
/* ************************************************************************** */
void	handle_heredoc(t_pipex *data);

/* ************************************************************************** */
/*                              COMMANDS FUNCTIONS                            */
/* ************************************************************************** */
char	*find_path(char *cmd, char **env);
void	execute_cmd(t_pipex *data, char *cmd, char **env);

/* ************************************************************************** */
/*                              CLEAN UP FUNCTIONS                            */
/* ************************************************************************** */
void	close_all_pipes(t_pipex *data);
void	close_fd(int fd);
void	free_parent(t_pipex *data);
void	free_pipe_fds(int **pipe_fds, int i);

/* ************************************************************************** */
/*                              ERROR FUNCTIONS                               */
/* ************************************************************************** */
void	ft_exit(char *str, t_pipex *data);

#endif
