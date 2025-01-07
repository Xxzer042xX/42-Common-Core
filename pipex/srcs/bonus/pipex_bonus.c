/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:39:17 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/07 17:45:57 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5)
		error_exit(ERR_INPUT);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			error_exit(ERR_INPUT);
		handle_heredoc(&pipex, av, ac);
		init_pipex(&pipex, ac - 1, ++av, env);
	}
	else
		init_pipex(&pipex, ac, av, env);
	execute_pipex_bonus(&pipex);
	free_pipex(&pipex);
	return (0);
}
