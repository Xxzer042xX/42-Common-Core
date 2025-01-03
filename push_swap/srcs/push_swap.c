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

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	int		status;

	a = NULL;
	b = NULL;
	if (ac < 2)
		return (SUCCESS);
	if (init_stack('a', &a) != SUCCESS || init_stack('b', &b) != SUCCESS)
		return (cleanup(a, NULL, ERR_MALLOC), ERR_MALLOC);
	status = parse_args(ac - 1, ++av, a);
	if (status != SUCCESS)
		return (cleanup(a, b, status), status);
	if (is_sorted(a) == SORTED)
		return (cleanup(a, b, SUCCESS), SUCCESS);
	index_stack(a);
	choose_algo(a, b);
	return (cleanup(a, b, SUCCESS), SUCCESS);
}
