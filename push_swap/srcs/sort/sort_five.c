/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:08:53 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/25 13:08:53 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	sort_five(t_stack *a, t_stack *b)
{
	int	min;
	int	max;
	int	pos;

	min = get_min(a);
	max = get_max(a);
	while (a->size > 3)
	{
		pos	= 0;
		if (a->first_node->value == min || a->first_node->value == max)
			pb(a, b);
		else
		{
			pos++;
			if (pos > a->size/2)
				rra(a);
			else
				ra(a);
		}
	}
	sort_three(a);
	if (b->size == 2 && b->first_node->value < b->last_node->value)
		sb(b);
	pa(a, b);
	pa(a, b);
	if (a->first_node->value == max)
		ra(a);
}
