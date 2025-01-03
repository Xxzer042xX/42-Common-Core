/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_minus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:07:05 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/06 13:39:12 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_int_minus_sub(t_flags *flags, int to_print, int *n);

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
