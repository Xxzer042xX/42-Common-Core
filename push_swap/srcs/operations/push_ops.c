/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:09:57 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/25 13:09:57 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction utilitaire qui déplace l'élément au sommet d'une pile vers      */
/*   le sommet d'une autre pile.                                              */
/*                                                                            */
/*   Cette fonction statique effectue les opérations suivantes :              */
/*   1. Extraction du premier noeud de la pile source                         */
/*   2. Mise à jour des pointeurs de la pile source                           */
/*   3. Insertion du noeud au sommet de la pile destination                   */
/*   4. Mise à jour des pointeurs de la pile destination                      */
/*   5. Mise à jour des compteurs de taille des deux piles                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - src : pointeur vers la pile source                                     */
/*   - dst : pointeur vers la pile destination                                */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	push(t_stack *src, t_stack *dst)
{
	t_node	*temp;

	if (!src || !src->first_node)
		return ;
	temp = src->first_node;
	src->first_node = src->first_node->next;
	if (src->first_node)
		src->first_node->prev = NULL;
	else
		src->last_node = NULL;
	src->size--;
	temp->next = dst->first_node;
	if (dst->first_node)
		dst->first_node->prev = temp;
	dst->first_node = temp;
	if (!dst->last_node)
		dst->last_node = temp;
	dst->size++;
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui déplace le premier élément de la pile B vers la pile A.     */
/*                                                                            */
/*   Implémente l'instruction 'pa' (push a) du sujet :                        */
/*   - Prend le premier élément de B et le place au sommet de A               */
/*   - Affiche "pa" sur la sortie standard                                    */
/*   - Ne fait rien si B est vide                                             */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile A                                            */
/*   - b : pointeur vers la pile B                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	pa(t_stack *a, t_stack *b)
{
	push(b, a);
	ft_printf("pa\n");
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui déplace le premier élément de la pile A vers la pile B.     */
/*                                                                            */
/*   Implémente l'instruction 'pb' (push b) du sujet :                        */
/*   - Prend le premier élément de A et le place au sommet de B               */
/*   - Affiche "pb" sur la sortie standard                                    */
/*   - Ne fait rien si A est vide                                             */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile A                                            */
/*   - b : pointeur vers la pile B                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	pb(t_stack *a, t_stack *b)
{
	push(a, b);
	ft_printf("pb\n");
}
