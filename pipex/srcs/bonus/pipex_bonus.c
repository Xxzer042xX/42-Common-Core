/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:46:48 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 14:47:49 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	data;

	if (ac < 5)
	{
		print_error_args();
		exit(EXIT_FAILURE);
	}
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		if (ac < 6)
			ft_exit("Error: Not enough arguments for here_doc", &data);
		data.here_doc = 1;
		data.limiter = av[2];
	}
	else
		data.here_doc = 0;
	init_app(&data, ac, av, env);
	create_processes(&data, av);
	close_all_pipes(&data);
	wait_processes(&data);
	free_parent(&data);
	return (0);
}

void	print_error_args(void)
{
	ft_putstr_fd("Error: Invalid number of arguments\n", 2);
	ft_putstr_fd("Usage: ./pipex_bonus", 2);
	ft_putstr_fd(" <file1> <cmd1> <cmd2> <...> <file2>\n", 2);
	ft_putstr_fd("   or: ./pipex_bonus", 2);
	ft_putstr_fd(" here_doc LIMITER <cmd1> <cmd2> <file2>\n", 2);
}
