/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:10:11 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/25 13:10:11 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction utilitaire qui effectue une rotation sur une pile.              */
/*                                                                            */
/*   Cette fonction déplace le premier élément de la pile vers la fin :       */
/*   1. Vérifie les conditions de validité (pile existe et au moins 2 nodes)  */
/*   2. Sauvegarde le premier noeud                                           */
/*   3. Met à jour les pointeurs pour le nouveau premier noeud                */
/*   4. Place l'ancien premier noeud à la fin de la pile                      */
/*   5. Met à jour tous les pointeurs concernés                               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile à manipuler                              */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	rotate(t_stack *stack)
{
	t_node	*first;

	first = stack->first_node;
	stack->first_node = stack->first_node->next;
	stack->first_node->prev = NULL;
	stack->last_node->next = first;
	first->prev = stack->last_node;
	first->next = NULL;
	stack->last_node = first;
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui effectue une rotation sur la pile A.                        */
/*                                                                            */
/*   Implémente l'instruction 'ra' (rotate a) du sujet :                      */
/*   - Décale tous les éléments de la pile A vers le haut                     */
/*   - Le premier élément devient le dernier                                  */
/*   - Affiche "ra" sur la sortie standard                                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile A                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	ra(t_stack *a)
{
	rotate(a);
	ft_printf("ra\n");
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui effectue une rotation sur la pile B.                        */
/*                                                                            */
/*   Implémente l'instruction 'rb' (rotate b) du sujet :                      */
/*   - Décale tous les éléments de la pile B vers le haut                     */
/*   - Le premier élément devient le dernier                                  */
/*   - Affiche "rb" sur la sortie standard                                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - b : pointeur vers la pile B                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	rb(t_stack *b)
{
	rotate(b);
	ft_printf("rb\n");
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui effectue une rotation sur les deux piles.                   */
/*                                                                            */
/*   Implémente l'instruction 'rr' du sujet :                                 */
/*   - Effectue ra et rb simultanément                                        */
/*   - Décale tous les éléments des deux piles vers le haut                   */
/*   - Affiche "rr" sur la sortie standard                                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile A                                            */
/*   - b : pointeur vers la pile B                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	ft_printf("rr\n");
}
