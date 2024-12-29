/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:42:57 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/27 16:20:49 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

// utils/stack_utils.c
#include "../../include/push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	current = stack->first_node;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (UNSORTED);
		current = current->next;
	}
	return (SORTED);
}

void	choose_algo(t_stack *a, t_stack *b)
{
	ft_printf("%d\n", a->size);
	if (a->size == 2)
	{
		if (a->first_node->value > a->last_node->value)
			sa(a);
	}
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
		sort_four(a, b);
	else if (a->size == 5)
		sort_five(a, b);
	else
		sort_big(a, b);
}

int	get_min(t_stack *stack)
{
	t_node	*current;
	int		min;

	current = stack->first_node;
	min = current->value;
	while (current)
	{
		if (current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

int	get_max(t_stack *stack)
{
	t_node	*current;
	int		max;

	current = stack->first_node;
	max = current->value;
	while (current)
	{
		if (current->value > max)
			max = current->value;
		current = current->next;
	}
	return (max);
}
