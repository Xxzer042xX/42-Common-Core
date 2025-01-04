/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:15:40 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/27 12:55:32 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction principale du programme push_swap qui trie une liste d'entiers. */
/*                                                                            */
/*   Le programme utilise deux piles pour effectuer le tri :                  */
/*   - Pile A : Contient initialement les nombres à trier                     */
/*   - Pile B : Pile auxiliaire vide au départ                                */
/*                                                                            */
/*   Processus de tri :                                                       */
/*   1. Initialisation des piles A et B                                       */
/*   2. Validation et parsing des arguments                                   */
/*   3. Vérification si la pile est déjà triée                                */
/*   4. Indexation des nombres pour optimiser le tri                          */
/*   5. Application de l'algorithme de tri approprié                          */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - ac : nombre d'arguments                                                */
/*   - av : tableau des arguments (chaînes de caractères)                     */
/*                                                                            */
/*   Retourne :                                                               */
/*   - SUCCESS (0) en cas de succès                                           */
/*   - Code d'erreur approprié en cas d'échec                                 */
/*                                                                            */
/* ************************************************************************** */
int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	int		status;

	a = NULL;
	b = NULL;
	if (ac < 2)
		return (SUCCESS);
	if (init_stack('a', &a) != SUCCESS || init_stack('b', &b) != SUCCESS)
		return (cleanup(a, NULL, ERR_MALLOC));
	status = parse_args(ac - 1, ++av, a);
	if (status != SUCCESS)
		return (cleanup(a, b, status));
	if (is_sorted(a) == SORTED)
		return (cleanup(a, b, SUCCESS));
	index_stack(a);
	choose_algo(a, b);
	return (cleanup(a, b, SUCCESS));
}
