/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
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
/*   Fonction principale du programme pipex.                                  */
/*                                                                            */
/*   Programme qui simule le comportement d'un pipe shell (|) et              */
/*   des redirections (<, >). Il permet d'exécuter deux commandes             */
/*   en séquence en redirigeant leurs entrées/sorties.                        */
/*                                                                            */
/*   Format attendu :                                                         */
/*   ./pipex file1 cmd1 cmd2 file2                                            */
/*   Équivalent shell : < file1 cmd1 | cmd2 > file2                           */
/*                                                                            */
/*   Exemple :                                                                */
/*   ./pipex infile "ls -l" "wc -l" outfile                                   */
/*   Équivalent à : < infile ls -l | wc -l > outfile                          */
/*                                                                            */
/*   Flux d'exécution :                                                       */
/*   1. Vérification du nombre d'arguments (doit être 4)                      */
/*   2. Initialisation de la structure de données                             */
/*      - Allocation des pipes                                                */
/*      - Ouverture des fichiers                                              */
/*   3. Création de deux processus enfants                                    */
/*      - Premier processus : exécute cmd1, lit infile, écrit dans pipe       */
/*      - Second processus : exécute cmd2, lit du pipe, écrit dans outfile    */
/*   4. Exécution :                                                           */
/*      - Création des processus enfants (create_processes)                   */
/*      - Attente et collecte des statuts (wait_processes)                    */
/*   5. Nettoyage complet des ressources (free_parent)                        */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - ac : nombre d'arguments (doit être 5)                                  */
/*   - av : tableau des arguments [prog, file1, cmd1, cmd2, file2]            */
/*   - env : variables d'environnement pour execve                            */
/*                                                                            */
/*   Retourne :                                                               */
/*   - Le statut de sortie du dernier processus en cas de succès              */
/*   - EXIT_FAILURE en cas d'erreur d'arguments ou d'exécution                */
/*                                                                            */
/* ************************************************************************** */
int	main(int ac, char **av, char **env)
{
	t_pipex	data;
	int		status;

	if (ac != 5)
		print_error_args();
	ft_memset(&data, 0, sizeof(t_pipex));
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
/*   Cette fonction affiche la syntaxe correcte du programme :                */
/*   ./pipex infile cmd1 cmd2 outfile                                         */
/*   Équivalent shell : < infile cmd1 | cmd2 > outfile                        */
/*                                                                            */
/*   Exemple d'utilisation valide :                                           */
/*   ./pipex input.txt "cat -e" "grep hello" output.txt                       */
/*   Équivalent à : < input.txt cat -e | grep hello > output.txt              */
/*                                                                            */
/*   Comportement :                                                           */
/*   - Affiche un message d'erreur sur stderr (fd 2)                          */
/*   - Affiche le format d'utilisation correct                                */
/*   - Termine le programme avec EXIT_FAILURE                                 */
/*                                                                            */
/* ************************************************************************** */
static void	print_error_args(void)
{
	ft_putstr_fd("Error: Invalid number of arguments\n", 2);
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	exit(EXIT_FAILURE);
}
