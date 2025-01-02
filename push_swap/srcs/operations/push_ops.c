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

void	pa(t_stack *a, t_stack *b)
{
	push(b, a);
	ft_printf("pa\n");
}

void	pb(t_stack *a, t_stack *b)
{
	push(a, b);
	ft_printf("pb\n");
}
