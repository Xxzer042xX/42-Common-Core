/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:32:02 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/05 02:43:14 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"

static int	ft_print_str_sub(t_flags *flags, char *str);
static int	ft_is_null(t_flags *flags);
static int	ft_proces(t_flags *flags, int printed_len, int total_width);

int	ft_print_str(va_list args, t_flags *flags)
{
	char	*str;

	if (flags->join)
		str = flags->join;
	else
		str = va_arg(args, char *);
	if (!str || flags->is_null)
		return (ft_is_null(flags));
	else
		return (ft_print_str_sub(flags, str));
}

static int	ft_is_null(t_flags *flags)
{
	int		str_len;
	int		printed_len;
	int		total_width;
	char	*str;

	if (flags->is_null)
		str = flags->join;
	else
		str = "(null)";
	flags->is_null = 1;
	str_len = ft_strlen(str);
	if (flags->dot && flags->prec < str_len)
		printed_len = flags->prec;
	else
		printed_len = str_len;
	if (flags->width > printed_len)
		total_width = flags->width;
	else
		total_width = printed_len;
	flags->join = str;
	return (ft_proces(flags, printed_len, total_width));
}

static int	ft_print_str_sub(t_flags *flags, char *str)
{
	int		str_len;
	int		printed_len;
	int		total_width;

	str_len = ft_strlen(str);
	if (flags->dot && flags->prec >= 0 && flags->prec < str_len)
		printed_len = flags->prec;
	else
		printed_len = str_len;
	if (flags->width > printed_len)
		total_width = flags->width;
	else
		total_width = printed_len;
	if (flags->join && flags->join != str)
		free(flags->join);
	flags->join = str;
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
