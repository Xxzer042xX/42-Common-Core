/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:32:20 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/04 20:33:42 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"
#include "../libft/libft.h"

/*
 Handles unsigned integer printing with formatting.
 Retrieves an unsigned int from args, converts it to a string, and sets
 formatting flags. Calls ft_print_int to handle the formatted output.
 */
int	ft_print_uint(va_list args, t_flags *flags)
{
	unsigned int	n;
	char			*str;

	n = va_arg(args, unsigned int);
	str = ft_ulltoa((unsigned long long)n);
	if (!str)
		return (-1);
	flags->join = str;
	flags->is_uintx = 1;
	return (ft_print_int(args, flags));
}
