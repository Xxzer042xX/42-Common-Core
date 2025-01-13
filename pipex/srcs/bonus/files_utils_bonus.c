/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:33:46 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/13 12:33:46 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	check_files_access(t_pipex *data, char **av)
{
	if (access(av[1], F_OK) == -1)
		ft_exit("Error: Input file does not exist", data);
	if (access(av[1], R_OK) == -1)
		ft_exit("Error: Input file permission denied", data);
}

void	open_files(t_pipex *data, int ac, char **av)
{
	if (data->here_doc)
	{
		handle_heredoc(data);
		data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		check_files_access(data, av);
		data->infile = open(av[1], O_RDONLY);
		if (data->infile < 0)
			ft_exit("Infile error", data);
		data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (data->outfile < 0)
		ft_exit("Outfile error", data);
}
