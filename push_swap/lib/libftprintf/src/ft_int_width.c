/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:07:17 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/06 14:22:48 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_width_prec_dot(t_flags *flags, int to_print, int *n);
static int	ft_width_dot(t_flags *flags, int to_print, int *n);
static int	ft_process_int_width(t_flags *flags, int to_print, int *n);

int	ft_int_width(t_flags *flags, int to_print, int *n)
{
	int	res;

	res = 0;
	res = ft_process_int_width(flags, to_print, n);
	if (res == -1)
		return (-1);
	else if (res == 0)
		return (0);
	if (flags->is_nega)
		ft_print_sign(flags, n);
	res = write(1, flags->join, to_print);
	if (res == -1)
		return (-1);
	*n += res;
	res = ft_pad_int(flags->prec - to_print, '0');
	if (res == -1)
		return (-1);
	*n += res;
	return (0);
}

static int	ft_process_int_width(t_flags *flags, int to_print, int *n)
{
	int	res;

	res = 0;
	if (flags->dot)
	{
		if (ft_width_dot(flags, to_print, n) == -1)
			return (-1);
		if (flags->join[0] == '0' && !flags->prec)
			return (0);
		else if (flags->prec < to_print)
			return (1);
	}
	if (flags->prec || flags->zero)
		return (ft_width_prec_dot(flags, to_print, n));
	else
	{
		res = ft_pad_int(flags->width - to_print - flags->is_nega, ' ');
		if (res == -1)
			return (-1);
		*n += res;
	}
	return (1);
}

static int	ft_width_dot(t_flags *flags, int to_print, int *n)
{
	int	res;

	res = 0;
	if (flags->prec < to_print)
	{
		if (flags->join[0] == '0' && !flags->prec)
			res = ft_pad_int(flags->width, ' ');
		else if (flags->space)
			res = ft_pad_int(1, ' ');
		else
			res = ft_pad_int(flags->width - to_print - flags->is_nega, ' ');
	}
	else
		res = ft_pad_int(flags->width - flags->prec - flags->is_nega, ' ');
	if (res == -1)
		return (-1);
	*n += res;
	return (0);
}

static int	ft_width_prec_dot(t_flags *flags, int to_print, int *n)
{
	int	res;

	res = ft_print_sign(flags, n);
	if (res == -1)
		return (-1);
	if (flags->zero && flags->width >= to_print && !flags->dot)
		res = ft_pad_int(flags->width - to_print - flags->is_nega, '0');
	else if (flags->zero && flags->prec < to_print && !flags->dot)
	{
		if (flags->prec > to_print)
			res = ft_pad_int(flags->width - flags->prec - flags->is_nega, '0');
	}
	else
		res = ft_pad_int(flags->prec - to_print, '0');
	if (res == -1)
		return (-1);
	*n += res;
	if ((!flags->prec && !flags->width) || (!flags->prec && flags->dot))
		return (0);
	res = write(1, flags->join, to_print);
	if (res == -1)
		return (-1);
	*n += res;
	return (0);
}
