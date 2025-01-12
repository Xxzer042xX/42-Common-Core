/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:46:48 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/12 14:47:49 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	data;
	int		child1_status;
	int		child2_status;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	init_app(&data, av, env);
	create_process(&data);
	if (waitpid(data.cpid1, &child1_status, 0) < 0)
	{
		perror("Error: Waitpid failed for process 1");
		exit(EXIT_FAILURE);
	}
	if (waitpid(data.cpid2, &child2_status, 0) < 0)
	{
		perror("Error: Waitpid failed for process 2");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(child1_status) && WIFEXITED(child2_status))
		return (WEXITSTATUS(child1_status) || WEXITSTATUS(child2_status));
	return (EXIT_FAILURE);
}
