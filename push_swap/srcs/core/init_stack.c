/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:43:02 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/01 19:43:02 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	init_stack(char id, t_stack **stack)
{
	*stack = malloc(sizeof(t_stack));
	if (!*stack)
		return (ERR_MALLOC);
	ft_memset(*stack, 0, sizeof(t_stack));
	(*stack)->id_stack = id;
	return (SUCCESS);
}
