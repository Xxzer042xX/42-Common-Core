/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_ops.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 22:02:37 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/31 22:02:37 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction utilitaire qui effectue une rotation inverse sur une pile.      */
/*                                                                            */
/*   Cette fonction déplace le dernier élément de la pile vers le sommet :    */
/*   1. Vérifie les conditions de validité (pile existe et au moins 2 nodes)  */
/*   2. Sauvegarde le dernier noeud                                           */
/*   3. Met à jour les pointeurs pour le nouveau dernier noeud                */
/*   4. Place l'ancien dernier noeud au sommet de la pile                     */
/*   5. Met à jour tous les pointeurs concernés                               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile à manipuler                              */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	reverse_rotate(t_stack *stack)
{
	t_node	*last;

	last = stack->last_node;
	stack->last_node = stack->last_node->prev;
	stack->last_node->next = NULL;
	last->next = stack->first_node;
	last->prev = NULL;
	stack->first_node->prev = last;
	stack->first_node = last;
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui effectue une rotation inverse sur la pile A.                */
/*                                                                            */
/*   Implémente l'instruction 'rra' (reverse rotate a) du sujet :             */
/*   - Décale tous les éléments de la pile A vers le bas                      */
/*   - Le dernier élément devient le premier                                  */
/*   - Affiche "rra" sur la sortie standard                                   */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile A                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	rra(t_stack *a)
{
	reverse_rotate(a);
	ft_printf("rra\n");
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui effectue une rotation inverse sur la pile B.                */
/*                                                                            */
/*   Implémente l'instruction 'rrb' (reverse rotate b) du sujet :             */
/*   - Décale tous les éléments de la pile B vers le bas                      */
/*   - Le dernier élément devient le premier                                  */
/*   - Affiche "rrb" sur la sortie standard                                   */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - b : pointeur vers la pile B                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	rrb(t_stack *b)
{
	reverse_rotate(b);
	ft_printf("rrb\n");
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui effectue une rotation inverse sur les deux piles.           */
/*                                                                            */
/*   Implémente l'instruction 'rrr' du sujet :                                */
/*   - Effectue rra et rrb simultanément                                      */
/*   - Décale tous les éléments des deux piles vers le bas                    */
/*   - Affiche "rrr" sur la sortie standard                                   */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile A                                            */
/*   - b : pointeur vers la pile B                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	rrr(t_stack *a, t_stack *b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	ft_printf("rrr\n");
}
