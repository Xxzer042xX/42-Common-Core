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
	t_node	*current;

	if (!a || !a->head || !a->head->next)
		return ;
	first = a->head;
	a->head = first->next;
	current = a->head;
	while (current->next)
		current = current->next;
	current->next = first;
	first->next = NULL;
	write(1, "ra\n", 3);
}

void	rb(t_stack *b)
{
	t_node	*first;
	t_node	*current;

	if (!b || !b->head || !b->head->next)
		return ;
	first = b->head;
	b->head = first->next;
	current = b->head;
	while (current->next)
		current = current->next;
	current->next = first;
	first->next = NULL;
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
	t_node	*current;

	if (!a || !a->head || !a->head->next)
		return ;
	current = a->head;
	while (current->next->next)
		current = current->next;
	last = current->next;
	current->next = NULL;
	last->next = a->head;
	a->head = last;
	write(1, "rra\n", 4);
}

void	rrb(t_stack *b)
{
	t_node	*last;
	t_node	*current;

	if (!b || !b->head || !b->head->next)
		return ;
	current = b->head;
	while (current->next->next)
		current = current->next;
	last = current->next;
	current->next = NULL;
	last->next = b->head;
	b->head = last;
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b)
{
	rra(a);
	rrb(b);
	write(1, "rrr\n", 4);
}
