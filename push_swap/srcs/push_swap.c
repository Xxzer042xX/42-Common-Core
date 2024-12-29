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
	int		status;

	a = NULL;
	b = NULL;
	if (ac < 2)
		return (error_exit(ERR_ARGS));
	if (init_stack('a', &a) != SUCCESS)
		return (error_exit(ERR_MALLOC));
	if (init_stack('b', &b) != SUCCESS)
		return (free_stack(a), error_exit(ERR_MALLOC));
	if (parse_args(ac - 1, ++av, a) != SUCCESS)
		return (free_stack(a), free_stack(b), error_exit(ERR_ARGS));
	status = is_sorted(a);
	if (status == SORTED)
		return (free_stack(a), free_stack(b), SUCCESS);
	choose_algo(a, b);
	return (free_stack(a), free_stack(b), SUCCESS);
}
