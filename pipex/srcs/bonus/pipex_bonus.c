/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:46:48 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/15 10:42:30 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	print_error_args(void);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction principale du programme pipex bonus.                            */
/*                                                                            */
/*   Programme qui simule le comportement des pipes shell (|) et              */
/*   redirections (<, >, <<, >>). Il permet d'exécuter plusieurs commandes    */
/*   en chaîne en redirigeant leurs entrées/sorties.                          */
/*                                                                            */
/*   Modes supportés :                                                        */
/*   1. Mode standard : file1 cmd1 cmd2 ... cmdN file2                        */
/*      Équivalent à : < file1 cmd1 | cmd2 | ... | cmdN > file2               */
/*   2. Mode here_doc : here_doc LIMITER cmd1 cmd2 file2                      */
/*      Équivalent à : cmd1 << LIMITER | cmd2 >> file2                        */
/*                                                                            */
/*   Flux d'exécution :                                                       */
/*   1. Vérification des arguments                                            */
/*   2. Initialisation (init_app)                                             */
/*   3. Création des processus (create_processes)                             */
/*   4. Attente des processus (wait_processes)                                */
/*   5. Nettoyage des ressources                                              */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - ac : nombre d'arguments                                                */
/*   - av : tableau des arguments                                             */
/*   - env : variables d'environnement                                        */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Le statut de sortie du dernier processus en cas de succès              */
/*   - EXIT_FAILURE en cas d'erreur                                           */
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
			ft_exit("invalid nbr args for here_doc", NULL, EXIT_FAILURE);
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
/*   Cette fonction affiche la syntaxe correcte du programme avec :           */
/*   1. Mode standard :                                                       */
/*      ./pipex_bonus input.txt "ls -l" "wc -l" output.txt                    */
/*      Équivalent shell : < input.txt ls -l | wc -l > output.txt             */
/*                                                                            */
/*   2. Mode here_doc :                                                       */
/*      ./pipex_bonus here_doc EOF "grep hello" "wc -l" output.txt            */
/*      Équivalent shell : grep hello << EOF | wc -l >> output.txt            */
/*                                                                            */
/*   Comportement :                                                           */
/*   - Affiche les messages sur stderr (fd 2)                                 */
/*   - Termine le programme avec EXIT_FAILURE                                 */
/*                                                                            */
/* ************************************************************************** */
static void	print_error_args(void)
{
	ft_putstr_fd("Error: Invalid number of arguments\n", 2);
	ft_putstr_fd("Usage: ./bin/pipex_bonus", 2);
	ft_putstr_fd(" <file1> <cmd1> <cmd2> <...> <file2>\n", 2);
	ft_putstr_fd("   or: ./bin/pipex_bonus", 2);
	ft_putstr_fd(" here_doc LIMITER <cmd1> <cmd2> <file2>\n", 2);
	exit(EXIT_FAILURE);
}
