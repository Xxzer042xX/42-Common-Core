/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:26:28 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/06 14:52:04 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_print_sign(t_flags *flags, int *count)
{
	if (flags->is_uintx)
		return (0);
	if (!flags->is_nega && flags->plus)
	{
		if (write(1, "+", 1) == -1)
			return (-1);
		*count += 1;
	}
	else if (!flags->is_nega && flags->space)
	{
		if (!flags->dot || flags->prec >= flags->width)
		{
			if (write(1, " ", 1) == -1)
				return (-1);
			*count += 1;
		}
	}
	else if (flags->is_nega == 1)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		*count += 1;
	}
	return (0);
}
