/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:09:46 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/25 13:09:46 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction utilitaire qui échange les deux premiers éléments d'une pile.   */
/*                                                                            */
/*   Cette fonction effectue un échange (swap) des valeurs :                  */
/*   1. Vérifie les conditions de validité (pile existe et au moins 2 nodes)  */
/*   2. Sauvegarde la valeur du premier noeud                                 */
/*   3. Échange les valeurs entre le premier et le second noeud               */
/*   4. Laisse les pointeurs intacts, seules les valeurs sont modifiées       */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile à manipuler                              */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	swap(t_stack *stack)
{
	int	temp;

	temp = stack->first_node->value;
	stack->first_node->value = stack->first_node->next->value;
	stack->first_node->next->value = temp;
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui échange les deux premiers éléments de la pile A.            */
/*                                                                            */
/*   Implémente l'instruction 'sa' (swap a) du sujet :                        */
/*   - Échange les positions des deux premiers éléments de la pile A          */
/*   - Ne fait rien s'il n'y a qu'un seul ou aucun élément                    */
/*   - Affiche "sa" sur la sortie standard                                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile A                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	sa(t_stack *a)
{
	swap(a);
	ft_printf("sa\n");
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui échange les deux premiers éléments de la pile B.            */
/*                                                                            */
/*   Implémente l'instruction 'sb' (swap b) du sujet :                        */
/*   - Échange les positions des deux premiers éléments de la pile B          */
/*   - Ne fait rien s'il n'y a qu'un seul ou aucun élément                    */
/*   - Affiche "sb" sur la sortie standard                                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - b : pointeur vers la pile B                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	sb(t_stack *b)
{
	swap(b);
	ft_printf("sb\n");
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction qui échange les premiers éléments des deux piles.               */
/*                                                                            */
/*   Implémente l'instruction 'ss' du sujet :                                 */
/*   - Effectue sa et sb simultanément                                        */
/*   - Échange les deux premiers éléments de chaque pile                      */
/*   - Affiche "ss" sur la sortie standard                                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile A                                            */
/*   - b : pointeur vers la pile B                                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	ss(t_stack *a, t_stack *b)
{
	swap(a);
	swap(b);
	ft_printf("ss\n");
}
