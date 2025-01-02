/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:32:22 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/24 22:32:22 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/push_swap.h"

void	print_error(int error)
{
	ft_putstr_fd("Error: ", 2);
	if (error == ERR_ARGS)
		ft_putstr_fd("Invalide arguments\n", 2);
	else if (error == ERR_MALLOC)
		ft_putstr_fd("Memory allocation failed\n", 2);
	else if (error == DEBUG)
		ft_putstr_fd("et ben faut bosser tes examens\n", 2);
}
