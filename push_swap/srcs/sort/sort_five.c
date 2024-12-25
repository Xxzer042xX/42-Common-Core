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

	min = get_min(a);
	max = get_max(a);
	while (a->size > 3)
	{
		if (a->head->value == min || a->head->value == max)
			pb(a, b);
		else
			ra(a);
	}
	sort_three(a);
	while (b->size)
		pa(a, b);
}
