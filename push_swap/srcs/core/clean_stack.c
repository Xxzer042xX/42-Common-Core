/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:34:03 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/01 19:34:03 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	free_stack(t_stack *stack);

void	cleanup(t_stack *a, t_stack *b, int status)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	if (status != SUCCESS)
		print_error(status);
}

static void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	if (!stack)
		return ;
	current = stack->first_node;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(stack);
}
