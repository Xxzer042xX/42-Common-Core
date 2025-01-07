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

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found: "
# define ERR_FORK "Fork"

/* ************************************************************************** */
/*                              OWN LIB                                       */
/* ************************************************************************** */
# include "../lib/libftprintf/include/ft_printf.h"
# include "../lib/libftprintf/libft/libft.h"

/* ************************************************************************** */
/*                             STANDAR LIB                                    */
/* ************************************************************************** */
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>

/* ************************************************************************** */
/*                             STRUCTURE DATA                                 */
/* ************************************************************************** */
typedef struct s_cmd
{
	char	**args;// Command arguments array
	char	*path;// Full path to executable
	int		pipe[2];// Pipe file descriptors
	pid_t	pid;// Process ID
}	t_cmd;

typedef struct s_pipex
{
	int		infile;// Input file descriptor
	int		outfile;// Output file descriptor
	int		cmd_count;// Number of commands
	char	**env;// Environment variables
	t_cmd	*cmds;// Array of commands
}	t_pipex;

/* ************************************************************************** */
/*                              MANDATORY PARTS                               */
/* ************************************************************************** */
/* Function prototypes - Core */
void	error_exit(char *error);
void	cmd_error_exit(char *cmd);
void	init_pipex(t_pipex *pipex, int ac, char **av, char **env);
void	free_pipex(t_pipex *pipex);

/* Function prototypes - Command utils */
char	*find_path(char *cmd, char **env);
void	execute_cmd(t_cmd *cmd, char **env);
void	parse_cmd(t_cmd *cmd, char *arg, char **env);

/* Function prototypes - Pipe utils */
void	create_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	redirect_io(t_pipex *pipex, t_cmd *cmd, int i);

/* Function prototypes - File utils */
void	open_files(t_pipex *pipex, char **av, int ac);
void	close_files(t_pipex *pipex);

/* ************************************************************************** */
/*                                BONUS PARTS                                 */
/* ************************************************************************** */
/* Function prototypes - Bonus */
void	handle_heredoc(t_pipex *pipex, char **av, int ac);
void	execute_pipex_bonus(t_pipex *pipex);

#endif
