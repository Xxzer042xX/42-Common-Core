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

static void	print_error_args(void);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction principale du programme pipex bonus.                            */
/*                                                                            */
/*   Cette fonction gère le flux principal du programme en :                  */
/*   1. Vérifiant le nombre d'arguments                                       */
/*   2. Initialisant la structure de données                                  */
/*   3. Gérant le mode here_doc si activé                                     */
/*   4. Créant et gérant les processus pour l'exécution des commandes         */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - ac : nombre d'arguments                                                */
/*   - av : tableau des arguments                                             */
/*   - env : variables d'environnement                                        */
/*                                                                            */
/*   Retourne :                                                               */
/*   - EXIT_SUCCESS en cas de succès                                          */
/*   - EXIT_FAILURE en cas d'erreur (via print_error_args)                    */
/*                                                                            */
/* ************************************************************************** */
int	main(int ac, char **av, char **env)
{
	t_pipex	data;
	int		status;

	if (ac < 5)
		print_error_args();
	ft_memset(&data, 0, sizeof(t_pipex));
	data.here_doc = (!ft_strcmp(av[1], "here_doc"));
	if (data.here_doc)
	{
		if (ac < 6)
			ft_exit("Error: Invalid number of arguments for here_doc", NULL);
		data.limiter = av[2];
	}
	init_app(&data, ac, av, env);
	create_processes(&data, av);
	status = wait_processes(&data);
	free_parent(&data);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'affichage des erreurs d'arguments.                            */
/*                                                                            */
/*   Cette fonction affiche sur la sortie d'erreur (fd 2) :                   */
/*   1. Un message d'erreur sur le nombre d'arguments invalide                */
/*   2. L'utilisation correcte du programme                                   */
/*   3. Les deux syntaxes possibles (normale et here_doc)                     */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - Aucun                                                                  */
/*                                                                            */
/*   Comportement :                                                           */
/*   - Termine le programme avec EXIT_FAILURE après l'affichage               */
/*                                                                            */
/* ************************************************************************** */
static void	print_error_args(void)
{
	ft_putstr_fd("Error: Invalid number of arguments\n", 2);
	ft_putstr_fd("Usage: ./pipex_bonus", 2);
	ft_putstr_fd(" <file1> <cmd1> <cmd2> <...> <file2>\n", 2);
	ft_putstr_fd("   or: ./pipex_bonus", 2);
	ft_putstr_fd(" here_doc LIMITER <cmd1> <cmd2> <file2>\n", 2);
	exit(EXIT_FAILURE);
}
