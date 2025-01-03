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

static void	rotate(t_stack *stack)
{
	t_node	*first;

	if (!stack || !stack->first_node || !stack->first_node->next)
		return ;
	first = stack->first_node;
	stack->first_node = stack->first_node->next;
	stack->first_node->prev = NULL;
	stack->last_node->next = first;
	first->prev = stack->last_node;
	first->next = NULL;
	stack->last_node = first;
}

void	ra(t_stack *a)
{
	rotate(a);
	ft_printf("ra\n");
}

void	rb(t_stack *b)
{
	rotate(b);
	ft_printf("rb\n");
}

void	rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	ft_printf("rr\n");
}
