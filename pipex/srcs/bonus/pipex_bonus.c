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
/*   redirections (<, >, <<, >>). Permet d'exécuter une série de commandes    */
/*   en redirigeant leurs entrées/sorties de manière chainée.                 */
/*                                                                            */
/*   Modes supportés :                                                        */
/*   1. Mode standard : Multiples pipes                                       */
/*      Format : ./pipex file1 cmd1 cmd2 ... cmdN file2                       */
/*      Shell : < file1 cmd1 | cmd2 | ... | cmdN > file2                      */
/*      Ex : ./pipex in "ls -l" "grep .c" "wc -l" out                         */
/*                                                                            */
/*   2. Mode here_doc : Entrée interactive                                    */
/*      Format : ./pipex here_doc LIMITER cmd1 cmd2 file2                     */
/*      Shell : cmd1 << LIMITER | cmd2 >> file2                               */
/*      Ex : ./pipex here_doc EOF "grep hello" "wc -l" out                    */
/*                                                                            */
/*   Flux d'exécution :                                                       */
/*   1. Validation des arguments (minimum 4 + cas spécial here_doc)           */
/*   2. Configuration initiale :                                              */
/*      - Détection du mode (standard/here_doc)                               */
/*      - Initialisation de la structure de données                           */
/*   3. Préparation du pipeline :                                             */
/*      - Initialisation des pipes et processus (init_app)                    */
/*      - Configuration des fichiers d'entrée/sortie                          */
/*   4. Exécution :                                                           */
/*      - Création des processus enfants (create_processes)                   */
/*      - Attente et collecte des statuts (wait_processes)                    */
/*   5. Nettoyage complet des ressources (free_parent)                        */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - ac : nombre d'arguments (min 5 en standard, 6 en here_doc)             */
/*   - av : tableau des arguments du programme                                */
/*   - env : variables d'environnement pour execve                            */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Statut de sortie du dernier processus si succès                        */
/*   - EXIT_FAILURE si erreur d'arguments ou d'exécution                      */
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
/*   - Affiche le format d'utilisation correct                                */
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
