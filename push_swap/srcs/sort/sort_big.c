/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:08:58 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/25 13:08:58 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

static void	radix_sort(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	size;
	int	i;
	int	j;

	size = a->size;
	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if ((a->first_node->value >> i) & 1)
				ra(a);
			else
				pb(a, b);
			j++;
		}
		while (b->size)
			pa(a, b);
		i++;
	}
}


static void	normalize_stack(t_stack *a)
{
	t_node	*current;
	t_node	*compare;
	int		rank;

	if (!a || !a->first_node)
		return ;
	current = a->first_node;
	while (current)
	{
		rank = 0;
		compare = a->first_node;
		while (compare)
		{
			if (compare->value < current->value)
				rank++;
			compare = compare->next;
		}
		current->value = rank;
		current = current->next;
	}
}

void	sort_big(t_stack *a, t_stack *b)
{
	normalize_stack(a);
	radix_sort(a, b);
}
