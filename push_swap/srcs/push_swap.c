/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:15:40 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/25 23:12:38 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;

	if (ac < 2)
		return (error_exit(ERR_ARGS));
	a = parse_args(ac, av);
	if (!a)
		return (error_exit(ERR_ARGS));
	b = init_stack('b');
	if (!b)
		return (free_stack(a), error_exit(ERR_MALLOC));
	if (!is_sorted(a))
		choose_algo(a, b);
	cleanup_app(a, b);
	return (0);
}
