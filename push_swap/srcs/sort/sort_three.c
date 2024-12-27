/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:08:41 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/27 16:20:58 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	sort_three(t_stack *a)
{
	int	min;

	min = get_min(a);
	if (a->head->value == min)
	{
		if (a->head->next->value > a->head->next->next->value)
			sa(a);
	}
	else if (a->head->next->value == min)
	{
		if (a->head->value > a->head->next->next->value)
			ra(a);
		else
			sa(a);
	}
	else
	{
		if (a->head->value > a->head->next->value)
			rra(a);
		else
			ra(a);
	}
}
