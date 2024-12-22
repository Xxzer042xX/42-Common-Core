/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_minus_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:07:05 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/06 13:39:12 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

static int	ft_int_minus_sub(t_flags *flags, int to_print, int *n);

/*
 Handles the printing of integers with left-alignment and proper padding.
 This function ensures the correct handling of width, precision, and sign, 
 and prints the formatted integer. If there is a dot (precision modifier),
 it adjusts the padding accordingly.
 */
int	ft_int_minus(t_flags *flags, int to_print, int *n)
{
	int	res;

	res = 0;
	if (ft_int_minus_sub(flags, to_print, n) == -1)
		return (-1);
	if (flags->dot && !flags->prec && flags->join[0] == '0')
		to_print = 0;
	res = write(1, flags->join, to_print);
	if (res == -1)
		return (-1);
	*n += res;
	if (flags->prec < to_print && flags->dot)
		res = ft_pad_int(flags->width - to_print - flags->is_nega, ' ');
	else if (flags->prec >= to_print && flags->dot)
		res = ft_pad_int(flags->width - flags->prec - flags->is_nega, ' ');
	else
		res = ft_pad_int(flags->width - to_print - flags->is_nega, ' ');
	if (res == -1)
		return (-1);
	*n += res;
	return (0);
}

/*
 ft_int_minus_sub - Handles initial formatting and sign printing for integers.
 This function is responsible for printing the sign (if applicable) and 
 adjusting the padding before printing the integer.
 Returns 0 on success or -1 if there is an error (e.g., write failure).
 */
static int	ft_int_minus_sub(t_flags *flags, int to_print, int *n)
{
	int	res;

	res = 0;
	if (ft_print_sign(flags, n) == -1)
		return (-1);
	if (flags->width)
		res = ft_pad_int(flags->prec - to_print, '0');
	if (flags->dot && !flags->width)
		res = ft_pad_int(flags->prec - to_print, '0');
	if (res == -1)
		return (-1);
	*n += res;
	return (0);
}
