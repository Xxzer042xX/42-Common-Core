/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:15:40 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/27 12:55:32 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	choose_algo(t_stack *a, t_stack *b);

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	int		status;

	a = NULL;
	b = NULL;
	if (ac < 2)
		return (print_error(ERR_ARGS), ERR_ARGS);
	if (init_stack('a', &a) != SUCCESS || init_stack('b', &b) != SUCCESS)
		return (cleanup(a, NULL, ERR_MALLOC), ERR_MALLOC);
	status = parse_args(ac - 1, ++av, a);
	if (status != SUCCESS)
		return (cleanup(a, b, status), status);
	if (is_sorted(a) == SORTED)
		return (cleanup(a, b, SUCCESS), SUCCESS);
	choose_algo(a, b);
	return (cleanup(a, b, SUCCESS), SUCCESS);
}

static void	choose_algo(t_stack *a, t_stack *b)
{
	if (!a || !b)
		return ;
	if (a->size == 2 && a->first_node->value > a->last_node->value)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
		sort_four(a, b);
	else if (a->size == 5)
		sort_five(a, b);
	else if (a->size > 5)
		sort_big(a, b);
}
