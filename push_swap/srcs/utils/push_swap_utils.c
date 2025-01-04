/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:42:57 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/27 16:20:49 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui vérifie si une pile est triée par ordre croissant.          */
/*                                                                            */
/*   La fonction parcourt la pile en comparant chaque élément avec le         */
/*   suivant pour vérifier que les valeurs sont dans l'ordre croissant.       */
/*                                                                            */
/*   Vérifications effectuées :                                               */
/*   1. Si la pile est vide ou n'existe pas, elle est considérée triée        */
/*   2. Compare chaque noeud avec son suivant                                 */
/*   3. Si une valeur est supérieure à la suivante, la pile n'est pas triée   */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile à vérifier                               */
/*                                                                            */
/*   Retourne :                                                               */
/*   - SORTED : si la pile est triée en ordre croissant                       */
/*   - UNSORTED : si la pile n'est pas triée                                  */
/*                                                                            */
/* ************************************************************************** */
int	is_sorted(t_stack *stack)
{
	t_node	*current;

	current = stack->first_node;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (UNSORTED);
		current = current->next;
	}
	return (SORTED);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui attribue des index aux éléments de la pile.                 */
/*                                                                            */
/*   Cette fonction assigne à chaque noeud un index basé sur sa position      */
/*   relative dans un tri croissant :                                         */
/*   1. Pour chaque noeud de la pile                                          */
/*   2. Compte combien d'éléments sont plus petits que lui                    */
/*   3. Assigne ce compte comme index du noeud                                */
/*                                                                            */
/*   Principe :                                                               */
/*   - L'index représente le nombre d'éléments plus petits                    */
/*   - Le plus petit élément aura l'index 0                                   */
/*   - Le plus grand élément aura l'index (taille - 1)                        */
/*   - Complexité : O(n²) où n est le nombre d'éléments                       */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile à indexer                                */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	index_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*compare;
	int		index;

	current = stack->first_node;
	while (current)
	{
		index = 0;
		compare = stack->first_node;
		while (compare)
		{
			if (compare->value < current->value)
				index++;
			compare = compare->next;
		}
		current->index = index;
		current = current->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui sélectionne et applique l'algorithme de tri approprié.      */
/*                                                                            */
/*   Choisit l'algorithme optimal en fonction de la taille de la pile :       */
/*   - 2 éléments : simple swap si nécessaire                                 */
/*   - 3 éléments : sort_three (tri optimisé pour 3 éléments)                 */
/*   - 4 éléments : sort_four (tri optimisé pour 4 éléments)                  */
/*   - 5 éléments : sort_five (tri optimisé pour 5 éléments)                  */
/*   - Plus de 5 éléments : sort_big (algorithme radix)                       */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile principale                                   */
/*   - b : pointeur vers la pile auxiliaire                                   */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	choose_algo(t_stack *a, t_stack *b)
{
	if (a->size == 2)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
		sort_four(a, b);
	else if (a->size == 5)
		sort_five(a, b);
	else
		sort_big(a, b);
}
