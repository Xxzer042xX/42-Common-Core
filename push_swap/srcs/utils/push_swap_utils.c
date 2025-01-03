/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:42:57 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/27 16:20:49 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->first_node)
		return (SORTED);
	current = stack->first_node;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (UNSORTED);
		current = current->next;
	}
	return (SORTED);
}

void	index_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*compare;
	int		index;

	current = stack->first_node;
	while (current)
	{
		index = 0;
		compare = stack->first_node;
		while (compare)
		{
			if (compare->value < current->value)
				index++;
			compare = compare->next;
		}
		current->index = index;
		current = current->next;
	}
}

void	choose_algo(t_stack *a, t_stack *b)
{
	if (!a || !b)
		return ;
	if (a->size == 2 && a->first_node->value > a->last_node->value)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
		sort_four(a, b);
	else if (a->size == 5)
		sort_five(a, b);
	else
	{
		index_stack(a);
		sort_big(a, b);
	}
}
