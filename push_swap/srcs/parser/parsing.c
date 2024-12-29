/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:40:14 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/27 17:33:56 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

static int	is_valid_number(char *str);
static int	check_duplicate(t_stack *stack, int num);
static int	add_to_stack(t_stack *stack, int num);

int	parse_args(int ac, char **av, t_stack *a)
{
	long	num;
	int		i;

	i = 0;
	while (i < ac)
	{
		if (is_valid_number(av[i]) != SUCCESS)
			return (ERR_ARGS);
		num = ft_atol(av[i]);
		if (num > MAX_INT || num < MIN_INT)
			return (ERR_ARGS);
		ft_printf("num = %d\n", (int)num);
		if (check_duplicate(a, (int)num) != SUCCESS)
			return (ERR_DUP);
		if (add_to_stack(a, (int)num) != SUCCESS)
			return (ERR_MALLOC);
		i++;
	}
	ft_printf("first = %d\n", a->first_node->value);
	ft_printf("last = %d\n", a->last_node->value);
	return (SUCCESS);
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (ERR_ARGS);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (ERR_ARGS);
		i++;
	}
	return (SUCCESS);
}

static int	check_duplicate(t_stack *stack, int num)
{
	t_node	*current;

	current = stack->first_node;
	while (current)
	{
		if (current->value == num)
			return (ERR_DUP);
		current = current->next;
	}
	return (SUCCESS);
}

static int	add_to_stack(t_stack *stack, int num)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (ERR_MALLOC);
	ft_memset(new, 0, sizeof(t_node));
	new->value = num;
	if (!stack->first_node)
	{
		stack->first_node = new;
		stack->last_node = new;
	}
	else
	{
		new->prev = stack->last_node;
		stack->last_node->next = new;
		stack->last_node = new;
	}
	stack->size++;
	return (SUCCESS);
}

