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

void	ra(t_stack *a)
{
	t_node	*first;

	if (!a || !a->first_node || !a->first_node->next)
		return ;
	first = a->first_node;
	a->first_node = first->next;
	a->first_node->prev = NULL;
	first->next = NULL;
	first->prev = a->last_node;
	a->last_node->next = first;
	a->last_node = first;
	write(1, "ra\n", 3);
}

void	rb(t_stack *b)
{
	t_node	*first;

	if (!b || !b->first_node || !b->first_node->next)
		return ;
	first = b->first_node;
	b->first_node = first->next;
	b->first_node->prev = NULL;
	first->next = NULL;
	first->prev = b->last_node;
	b->last_node->next = first;
	b->last_node = first;
	write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b)
{
	ra(a);
	rb(b);
	write(1, "rr\n", 3);
}

void	rra(t_stack *a)
{
	t_node	*last;

	if (!a || !a->first_node || !a->first_node->next)
		return ;
	last = a->last_node;
	a->last_node = last->prev;
	a->last_node->next = NULL;
	last->prev = NULL;
	last->next = a->first_node;
	a->first_node->prev = last;
	a->first_node = last;
	write(1, "rra\n", 4);
}

void	rrb(t_stack *b)
{
	t_node	*last;

	if (!b || !b->first_node || !b->first_node->next)
		return ;
	last = b->last_node;
	b->last_node = last->prev;
	b->last_node->next = NULL;
	last->prev = NULL;
	last->next = b->first_node;
	b->first_node->prev = last;
	b->first_node = last;
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b)
{
	rra(a);
	rrb(b);
	write(1, "rrr\n", 4);
}
