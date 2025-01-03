/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:55:56 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/01 23:55:56 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

static int	find_min_pos(t_stack *stack);
static void	rotate_to_min(t_stack *a);

void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	if (a->size != 3)
		return ;
	first = a->first_node->index;
	second = a->first_node->next->index;
	third = a->last_node->index;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}

void	sort_four(t_stack *a, t_stack *b)
{
	rotate_to_min(a);
	pb(a, b);
	sort_three(a);
	pa(a, b);
}

void	sort_five(t_stack *a, t_stack *b)
{
	if (!a || !b || !a->first_node || a->size != 5)
		return ;
	while (a->size > 3)
	{
		rotate_to_min(a);
		pb(a, b);
	}
	sort_three(a);
	while (b && b->size > 0)
		pa(a, b);
}

static void	rotate_to_min(t_stack *a)
{
	t_node	*temp;
	int		min_pos;
	int		min_index;

	if (!a || !a->first_node || a->size < 2)
		return ;
	min_index = a->first_node->index;
	temp = a->first_node;
	while (temp)
	{
		if (temp->index < min_index)
			min_index = temp->index;
		temp = temp->next;
	}
	while (a->first_node->index != min_index)
	{
		min_pos = find_min_pos(a);
		if (min_pos <= a->size / 2)
			ra(a);
		else
			rra(a);
	}
}

static int	find_min_pos(t_stack *stack)
{
	t_node	*current;
	int		min_pos;
	int		pos;

	if (!stack || !stack->first_node)
		return (0);
	current = stack->first_node;
	min_pos = 0;
	pos = 0;
	while (current)
	{
		if (current->index == 0)
			min_pos = pos;
		current = current->next;
		pos++;
	}
	return (min_pos);
}
