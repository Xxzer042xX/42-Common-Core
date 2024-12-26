/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:40:14 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/25 19:40:14 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_duplicate(t_stack *stack, int num)
{
	t_node	*current;

	current = stack->head;
	while (current)
	{
		if (current->value == num)
			return (1);
		current = current->next;
	}
	return (0);
}

static void	add_to_stack(t_stack *stack, int num)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return ;
	new->value = num;
	new->next = NULL;
	if (!stack->head)
	{
		stack->head = new;
		stack->tail = new;
	}
	else
	{
		stack->tail->next = new;
		stack->tail = new;
	}
	stack->size++;
}

/******************************************************************************/
/*																			  */
/*		1. Parse arguments and create stack a.								  */

t_stack	*parse_args(int ac, char **av)
{
	t_stack	*stack;
	long	num;
	int		i;

	stack = init_stack('a');
	if (!stack)
		return (NULL);
	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (free_stack(stack), NULL);
		num = ft_atol(av[i]);
		if (num > MAX_INT || num < MIN_INT)
			return (free_stack(stack), NULL);
		if (check_duplicate(stack, (int)num))
			return (free_stack(stack), NULL);
		add_to_stack(stack, (int)num);
		i++;
	}
	return (stack);
}
