/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:07:27 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/01 12:07:27 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

int	calculate_cost(t_stack *stack, int pos)
{
	if (pos <= stack->size / 2)
		return (pos);
	return (stack->size - pos);
}

void	update_cost(t_cost *cost, t_stack *a, t_stack *b, int pos_a)
{
	int	pos_b;

	if (!a || !b || !cost)
		return ;
	pos_b = find_position(b, cost->value);
	cost->moves_a = (pos_a <= a->size / 2) ? pos_a : -(a->size - pos_a);
	cost->moves_b = (pos_b <= b->size / 2) ? pos_b : -(b->size - pos_b);
	cost->total_cost = abs(cost->moves_a) + abs(cost->moves_b);
}

void	execute_move(t_stack *a, t_stack *b, t_cost *cost)
{
	while (cost->moves_a > 0 && cost->moves_b > 0)
	{
		rr(a, b);
		cost->moves_a--;
		cost->moves_b--;
	}
	while (cost->moves_a < 0 && cost->moves_b < 0)
	{
		rrr(a, b);
		cost->moves_a++;
		cost->moves_b++;
	}
	while (cost->moves_a > 0)
		ra(a);
	while (cost->moves_a < 0)
		rra(a);
	while (cost->moves_b > 0)
		rb(b);
	while (cost->moves_b < 0)
		rrb(b);
	pa(a, b);
}