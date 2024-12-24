/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:15:40 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/24 22:15:40 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int ac, char **av)
{
	(void)av;
	
	if (ac < 2)
		return (ERR_ARGS);
	write(1, "Hello, World!\n", 14);
	return (0);
}
