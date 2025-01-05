/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:55:56 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/01 23:55:56 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

static int	find_min_pos(t_stack *stack);
static void	rotate_to_min(t_stack *a);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de tri optimisée pour exactement trois éléments.                */
/*                                                                            */
/*   Implémente un tri par cas pour trois éléments :                          */
/*   - Compare les indices des trois éléments                                 */
/*   - Identifie le cas spécifique parmi les 5 possibles                      */
/*   - Applique la séquence d'instructions optimale pour ce cas               */
/*                                                                            */
/*   Cas traités :                                                            */
/*   1. first > second && second < third && first < third : sa                */
/*   2. first > second && second > third : sa + rra                           */
/*   3. first > second && second < third && first > third : ra                */
/*   4. first < second && second > third && first < third : sa + ra           */
/*   5. first < second && second > third && first > third : rra               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile à trier                                      */
/*                                                                            */
/* ************************************************************************** */
void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	first = a->first_node->index;
	second = a->first_node->next->index;
	third = a->last_node->index;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de tri optimisée pour exactement quatre éléments.               */
/*                                                                            */
/*   Stratégie de tri :                                                       */
/*   1. Place le plus petit élément au sommet de la pile                      */
/*   2. Déplace cet élément vers la pile B                                    */
/*   3. Trie les trois éléments restants avec sort_three                      */
/*   4. Ramène le plus petit élément au sommet de la pile A                   */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile principale                                   */
/*   - b : pointeur vers la pile auxiliaire                                   */
/*                                                                            */
/* ************************************************************************** */
void	sort_four(t_stack *a, t_stack *b)
{
	rotate_to_min(a);
	pb(a, b);
	sort_three(a);
	pa(a, b);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de tri optimisée pour exactement cinq éléments.                 */
/*                                                                            */
/*   Stratégie de tri :                                                       */
/*   1. Place et pousse les deux plus petits éléments vers B                  */
/*   2. Trie les trois éléments restants avec sort_three                      */
/*   3. Ramène les deux plus petits éléments de B vers A                      */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile principale                                   */
/*   - b : pointeur vers la pile auxiliaire                                   */
/*                                                                            */
/* ************************************************************************** */
void	sort_five(t_stack *a, t_stack *b)
{
	while (a->size > 3)
	{
		rotate_to_min(a);
		pb(a, b);
	}
	sort_three(a);
	while (b && b->size > 0)
		pa(a, b);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction utilitaire qui fait tourner la pile jusqu'au minimum.           */
/*                                                                            */
/*   Processus :                                                              */
/*   1. Trouve l'index minimum dans la pile                                   */
/*   2. Détermine la position de cet index                                    */
/*   3. Choisit la rotation optimale (ra ou rra) selon la position            */
/*   4. Effectue les rotations jusqu'à ce que le minimum soit au sommet       */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile à manipuler                                  */
/*                                                                            */
/* ************************************************************************** */
static void	rotate_to_min(t_stack *a)
{
	t_node	*temp;
	int		min_pos;
	int		min_index;

	min_index = a->first_node->index;
	temp = a->first_node;
	while (temp)
	{
		if (temp->index < min_index)
			min_index = temp->index;
		temp = temp->next;
	}
	while (a->first_node->index != min_index)
	{
		min_pos = find_min_pos(a);
		if (min_pos <= a->size / 2)
			ra(a);
		else
			rra(a);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction utilitaire qui trouve la position du minimum dans la pile.      */
/*                                                                            */
/*   Parcourt la pile pour trouver la position de l'élément avec index 0 :    */
/*   1. Initialise les compteurs et pointeurs                                 */
/*   2. Parcourt tous les noeuds                                              */
/*   3. Enregistre la position quand l'index 0 est trouvé                     */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile à analyser                               */
/*                                                                            */
/*   Retourne :                                                               */
/*   - La position de l'élément minimum dans la pile                          */
/*   - 0 si la pile est vide ou invalide                                      */
/*                                                                            */
/* ************************************************************************** */
static int	find_min_pos(t_stack *stack)
{
	t_node	*current;
	int		min_pos;
	int		pos;

	current = stack->first_node;
	min_pos = 0;
	pos = 0;
	while (current)
	{
		if (current->index == 0)
			min_pos = pos;
		current = current->next;
		pos++;
	}
	return (min_pos);
}
