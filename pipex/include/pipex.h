/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:01:01 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/07 17:45:29 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	pid_t	cpid1;
	pid_t	cpid2;
	char	**env;
	char	*cmd1;
	char	*cmd2;
	int		pipe_fd[2];
	int		infile;
	int		outfile;
}	t_pipex;

// Core functions
char	*find_path(char *cmd, char **env);
void	execute_cmd(char *cmd, char **env);
void	process_cmd(char *cmd, int fdin, int fdout, char **env);
void	create_process(t_pipex *data);

#endif
