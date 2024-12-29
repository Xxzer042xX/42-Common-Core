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

void	pa(t_stack *a, t_stack *b)
{
	t_node	*tmp;

	if (!b || !b->first_node)
		return ;
	tmp = b->first_node;
	b->first_node = tmp->next;
	if (b->first_node)
		b->first_node->prev = NULL;
	tmp->next = a->first_node;
	tmp->prev = NULL;
	if (a->first_node)
		a->first_node->prev = tmp;
	a->first_node = tmp;
	a->size++;
	b->size--;
	if (b->size == 0)
		b->last_node = NULL;
	if (a->size == 1)
		a->last_node = tmp;
	write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
	t_node	*tmp;

	if (!a || !a->first_node)
		return ;
	tmp = a->first_node;
	a->first_node = tmp->next;
	if (a->first_node)
		a->first_node->prev = NULL;
	tmp->next = b->first_node;
	tmp->prev = NULL;
	if (b->first_node)
		b->first_node->prev = tmp;
	b->first_node = tmp;
	b->size++;
	a->size--;
	if (a->size == 0)
		a->last_node = NULL;
	if (b->size == 1)
		b->last_node = tmp;
	write(1, "pb\n", 3);
}
