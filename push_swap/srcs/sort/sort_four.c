/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_four.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:21:38 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/29 14:21:38 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	sort_four(t_stack *a, t_stack *b)
{
	int	min;
	int	pos;

	min = get_min(a);
	pos = 0;
	while (pos < 4 && a->first_node->value != min)
	{
		ra(a);
		pos++;
	}
	if (pos > 2)
	{
		while (pos < 4)
		{
			rra(a);
			pos++;
		}
	}
	pb(a, b);
	sort_three(a);
	pa(a, b);
}
