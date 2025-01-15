/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:46:48 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/15 13:04:46 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction principale du programme pipex.                                  */
/*                                                                            */
/*   Cette fonction :                                                         */
/*   1. Vérifie le nombre d'arguments                                         */
/*   2. Initialise les données du programme                                   */
/*   3. Crée et gère les processus enfants                                    */
/*   4. Attend la fin des processus et retourne le statut approprié           */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - ac : nombre d'arguments                                                */
/*   - av : tableau des arguments                                             */
/*   - env : variables d'environnement                                        */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Le statut de sortie des processus enfants                              */
/*   - EXIT_FAILURE en cas d'erreur                                           */
/*                                                                            */
/* ************************************************************************** */
int	main(int ac, char **av, char **env)
{
	t_pipex	data;
	int		status;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	init_app(&data, av, env);
	create_process(&data);
	if (waitpid(data.cpid1, &status, 0) == -1)
	{
		perror("Error: Waitpid failed for process 1");
		exit(EXIT_FAILURE);
	}
	if (waitpid(data.cpid2, &status, 0) == -1)
	{
		perror("Error: Waitpid failed for process 2");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
