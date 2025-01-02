/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:10:47 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/01 12:10:47 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

int	find_position(t_stack *stack, int value)
{
	t_node	*current;
	int		pos;

	if (!stack || !stack->first_node)
		return (0);
	current = stack->first_node;
	pos = 0;
	while (current)
	{
		if (current->value == value)
			return (pos);
		current = current->next;
		pos++;
	}
	return (-1);
}

int find_min_pos(t_stack *stack)
{
    t_node  *current;
    int     min;
    int     min_pos;
    int     pos;

    // Ajout des vérifications de sécurité
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
int	find_max_position(t_stack *stack)
{
	t_node	*current;
	int		max;
	int		max_pos;
	int		pos;

	current = stack->first_node;
	max = current->value;
	max_pos = 0;
	pos = 0;
	while (current)
	{
		if (current->value > max)
		{
			max = current->value;
			max_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (max_pos);
}

int	find_insert_position(t_stack *a, int value)
{
	t_node	*current;
	int		min;
	int		max;
	int		pos;

	if (!a || !a->first_node)
		return (0);
	get_min_max(a, &min, &max);
	if (value < min || value > max)
		return (find_min_pos(a));
	current = a->first_node;
	pos = 0;
	while (current->next)
	{
		if (value > current->value && value < current->next->value)
			return (pos + 1);
		pos++;
		current = current->next;
	}
	return (0);
}


void    get_min_max(t_stack *stack, int *min, int *max)
{
    t_node  *current;

    if (!stack || !stack->first_node || !min || !max)
        return ;
    current = stack->first_node;
    *min = current->value;
    *max = current->value;
    while (current)
    {
        if (current->value < *min)
            *min = current->value;
        if (current->value > *max)
            *max = current->value;
        current = current->next;
    }
}