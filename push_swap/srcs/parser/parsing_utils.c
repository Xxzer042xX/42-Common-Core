/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:55:17 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/31 21:55:17 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

static int	convert_to_int(const char *str, int *num);
static int	check_duplicate(t_stack *stack, int num);
static int	add_to_stack(t_stack *stack, int num);

int	handle_numbers(t_stack *stack, char **numbers)
{
	int	i;
	int	status;

	i = 0;
	while (numbers && numbers[i])
	{
		status = process_number(stack, numbers[i]);
		if (status != SUCCESS)
			return (status);
		i++;
	}
	return (SUCCESS);
}

int	process_number(t_stack *stack, const char *str)
{
	int	num;

	if (convert_to_int(str, &num) != SUCCESS)
		return (ERR_ARGS);
	if (check_duplicate(stack, num) != SUCCESS)
		return (ERR_DUP);
	return (add_to_stack(stack, num));
}

static int	convert_to_int(const char *str, int *num)
{
	long	result;
	int		i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (!str[i])
		return (ERR_ARGS);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (ERR_ARGS);
		i++;
	}
	result = ft_atol(str);
	if (result > MAX_INT || result < MIN_INT)
		return (ERR_ARGS);
	*num = (int)result;
	return (SUCCESS);
}

static int	check_duplicate(t_stack *stack, int num)
{
	t_node	*current;

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

static int	add_to_stack(t_stack *stack, int num)
{
	t_node	*new;

	if (!stack)
		return (ERR_ARGS);
	new = malloc(sizeof(t_node));
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
		if (stack->last_node)
			stack->last_node->next = new;
		stack->last_node = new;
	}
	stack->size++;
	return (SUCCESS);
}
