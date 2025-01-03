/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:39:17 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/03 22:39:17 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < 5)
		error_exit(ERR_INPUT);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			error_exit(ERR_INPUT);
		handle_heredoc(&pipex, argv, argc);
		init_pipex(&pipex, argc - 1, argv + 1, env);
	}
	else
		init_pipex(&pipex, argc, argv, env);
	execute_pipex_bonus(&pipex);
	free_pipex(&pipex);
	return (0);
}
