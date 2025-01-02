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

static void	calculate_best_move(t_stack *a, t_stack *b, t_cost *cost)
{
    t_node	*current;
    t_cost	temp_cost;
    int		pos_b;
    int		pos_a;
    
    if (!a || !b || !cost || !b->first_node)
        return ;
        
    current = b->first_node;
    pos_b = 0;
    cost->total_cost = MAX_INT;
    
    while (current)
    {
        pos_a = find_insert_position(a, current->value);
        ft_memset(&temp_cost, 0, sizeof(t_cost));
        temp_cost.value = current->value;
        update_cost(&temp_cost, a, b, pos_a);
        
        if (temp_cost.total_cost < cost->total_cost)
        {
            cost->moves_a = temp_cost.moves_a;
            cost->moves_b = temp_cost.moves_b;
            cost->total_cost = temp_cost.total_cost;
            cost->value = temp_cost.value;
            cost->target_pos = pos_a;
        }
        current = current->next;
        pos_b++;
    }
}

static int	get_chunks_count(int size)
{
	if (size <= 100)
		return (5);
	return (11);
}

static void	push_to_b_in_chunks(t_stack *a, t_stack *b)
{
	int	min;
	int	max;
	int	chunk_size;
	int	chunks;
	int	current_limit;

	get_min_max(a, &min, &max);
	chunks = get_chunks_count(a->size);
	chunk_size = (max - min) / chunks;
	current_limit = min + chunk_size;
	while (a->size > 3)
	{
		if (a->first_node->value <= current_limit)
		{
			pb(a, b);
			if (b->size > 1 && b->first_node->value < b->first_node->next->value)
				rb(b);
		}
		else if (current_limit < max)
			current_limit += chunk_size;
		else
			ra(a);
	}
}

static void	move_back_to_a(t_stack *a, t_stack *b)
{
	t_cost	cost;

	while (b->size > 0)
	{
		ft_memset(&cost, 0, sizeof(t_cost));
		calculate_best_move(a, b, &cost);
		execute_move(a, b, &cost);
	}
}

void	sort_big(t_stack *a, t_stack *b)
{
	int	min_pos;

	if (!a || !b || a->size <= 5)
		return ;
	push_to_b_in_chunks(a, b);
	sort_three(a);
	move_back_to_a(a, b);
	min_pos = find_min_pos(a);
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