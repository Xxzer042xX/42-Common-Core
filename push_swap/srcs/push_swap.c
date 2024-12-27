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

/******************************************************************************/
/*                              MAIN FUNCTION                                 */
/*																			  */
/*		1. Parse arguments and create stack a.								  */
/*		2. Create stack b.												      */
/*		3. Check if stack a is sorted.										  */
/*		4. Choose algorithm based on stack size.							  */
/*		5. Cleanup and exit.												  */
/*																			  */
/******************************************************************************/
int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;

	if (ac < 2)
		return (error_exit(ERR_ARGS));
	a = parse_args(ac - 1, ++av);
	if (!a)
		return (error_exit(ERR_ARGS));
	b = init_stack('b');
	if (!b)
		return (free_stack(a), error_exit(ERR_MALLOC));
	if (!is_sorted(a))
		choose_algo(a, b);
	while (a->head->next)
	{
		ft_printf("%i\n", a->head->value);
		a->head->next++;
	}
	cleanup_app(a, b);
	return (0);
}
