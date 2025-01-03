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

static void	rotate_to_min(t_stack *a)
{
	int	min_pos;

	if (!a || !a->first_node || a->size < 2)
		return ;
	min_pos = find_min_pos(a);
	if (min_pos < 0 || min_pos >= a->size)
		return ;
	while (min_pos > 0)
	{
		if (min_pos <= a->size / 2)
		{
			ra(a);
			min_pos--;
		}
		else
		{
			rra(a);
			min_pos = (min_pos + 1) % a->size;
		}
	}
}

void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	if (a->size != 3)
		return ;
	first = a->first_node->value;
	second = a->first_node->next->value;
	third = a->last_node->value;
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
	if (!a || !b || !a->first_node)
		return ;
	if (a->size != 4)
		return ;
	rotate_to_min(a);
	if (a->size > 3)
		pb(a, b);
	if (a->size == 3)
		sort_three(a);
	if (b && b->size > 0)
		pa(a, b);
}

void	sort_five(t_stack *a, t_stack *b)
{
	int	initial_size;

	if (!a || !b || !a->first_node)
		return ;
	if (a->size != 5)
		return ;
	initial_size = a->size;
	while (a->size > 3 && initial_size == 5)
	{
		if (!a->first_node)
			break ;
		rotate_to_min(a);
		if (b && a->size > 3)
			pb(a, b);
	}
	if (a->size == 3)
		sort_three(a);
	while (b && b->size > 0)
		pa(a, b);
}

int	find_min_pos(t_stack *stack)
{
	t_node	*current;
	int		min;
	int		min_pos;
	int		pos;

	if (!stack || !stack->first_node)
		return (0);
	current = stack->first_node;
	min = current->value;
	min_pos = 0;
	pos = 0;
	while (current)
	{
		if (current->value < min)
		{
			min = current->value;
			min_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (min_pos);
}
