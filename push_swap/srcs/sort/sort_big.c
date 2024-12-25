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
			if ((a->head->value >> i) & 1)
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
	int		i;
	int		*array;
	int		rank;

	array = malloc(sizeof(int) * a->size);
	if (!array)
		return ;
	current = a->head;
	i = 0;
	while (current)
	{
		array[i++] = current->value;
		current = current->next;
	}
	current = a->head;
	while (current)
	{
		while (i < a->size)
		{
			if (array[i] < current->value)
				rank++;
			i++;
		}
		current->value = rank;
		current = current->next;
	}
	free(array);
}

void	sort_big(t_stack *a, t_stack *b)
{
	normalize_stack(a);
	radix_sort(a, b);
}
