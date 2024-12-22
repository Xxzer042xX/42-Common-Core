/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:31:52 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/28 20:40:52 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_proces(t_flags *flags, int printed_len, int total_width);

int	ft_print_char(va_list args, t_flags *flags)
{
	char	c;
	int		printed_len;
	int		total_width;

	if (flags->join)
		c = flags->join[0];
	else
		c = (char)va_arg(args, int);
	printed_len = 1;
	if (flags->width > printed_len)
		total_width = flags->width;
	else
		total_width = printed_len;
	flags->join = &c;
	return (ft_proces(flags, printed_len, total_width));
}

static int	ft_proces(t_flags *flags, int printed_len, int total_width)
{
	int	char_count;
	int	result;

	char_count = 0;
	if (flags->minus)
	{
		result = ft_print_str_prec(flags->join, printed_len);
		if (result == -1)
			return (-1);
		char_count += result;
		result = ft_print_str_padding(total_width - printed_len);
		if (result == -1)
			return (-1);
		char_count += result;
		return (char_count);
	}
	result = ft_print_str_padding(total_width - printed_len);
	if (result == -1)
		return (-1);
	char_count += result;
	result = ft_print_str_prec(flags->join, printed_len);
	if (result == -1)
		return (-1);
	char_count += result;
	return (char_count);
}
