/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:42:57 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/27 16:20:49 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

// src/utils/stack_utils.c

#include "../../include/push_swap.h"

int check_duplicate(t_stack *stack, int num)
{
    t_node  *current;

    if (!stack)
        return (ERR_ARGS);

    current = stack->first_node;
    while (current)
    {
        if (current->value == num)
            return (ERR_DUP);
        current = current->next;
    }
    return (SUCCESS);
}

int add_to_stack(t_stack *stack, int num)
{
    t_node  *new;

    // Vérification du pointeur stack
    if (!stack)
        return (ERR_ARGS);

    new = malloc(sizeof(t_node));
    if (!new)
        return (ERR_MALLOC);

    // Initialisation complète du nouveau node
    new->value = num;
    new->next = NULL;
    new->prev = NULL;
    new->index = 0;  // Si vous utilisez l'index

    // Cas où la stack est vide
    if (!stack->first_node)
    {
        stack->first_node = new;
        stack->last_node = new;
    }
    // Cas où la stack a déjà des éléments
    else
    {
        // Mise à jour des liens
        new->prev = stack->last_node;
        if (stack->last_node)  // Protection supplémentaire
            stack->last_node->next = new;
        stack->last_node = new;
    }
    stack->size++;
    return (SUCCESS);
}

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->first_node)
		return (SORTED);
	current = stack->first_node;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (UNSORTED);
		current = current->next;
	}
	return (SORTED);
}
