/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_dot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:07:26 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/05 18:07:26 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_int_dot(t_flags *flags, int to_print, int *n)
{
	int	res;

	res = 0;
	res = ft_print_sign(flags, n);
	if (res == -1)
		return (-1);
	*n += res;
	res = ft_pad_int(flags->prec - to_print, '0');
	if (res == -1)
		return (-1);
	*n += res;
	if (flags->join[0] == '0' && !flags->prec)
		return (0);
	res = write(1, flags->join, to_print);
	if (res == -1)
		return (-1);
	*n += res;
	return (0);
}
