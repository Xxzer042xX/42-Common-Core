/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 07:25:50 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/27 02:29:50 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"

static int	ft_dispatch_format(char format, va_list args, t_flags *flags);
static void	ft_parse_number(const char **format, t_flags *flags);
static void	ft_set_flag(const char **format, t_flags *flags);

// Fonction de parsing des flags et spécificateurs
int	ft_parsing(const char **format, va_list args, t_flags *flags)
{
	ft_memset(flags, 0, sizeof(t_flags));
	while (**format && !ft_strchr("cspdiuxX%", **format))
	{
		if (ft_isflags((int)**format))
			ft_set_flag(format, flags);
		else if (ft_isdigit(**format))
			ft_parse_number(format, flags);
		else
			format++;
	}
	if (**format)
		return (ft_dispatch_format(**format, args, flags));
	return (-1);
}

// Fonction pour assigner les flags
static void	ft_set_flag(const char **format, t_flags *flags)
{
	if (**format == '-')
		flags->minus = 1;
	else if (**format == '0')
		flags->zero = 1;
	else if (**format == '#')
		flags->hash = 1;
	else if (**format == '+')
		flags->plus = 1;
	else if (**format == ' ')
		flags->space = 1;
	else if (**format == '.')
		flags->dot = 1;
	(*format)++;
}

// Fonction pour lire les nombres dans le format
static void	ft_parse_number(const char **format, t_flags *flags)
{
	int	number;

	number = 0;
	while (ft_isdigit(**format))
	{
		number = number * 10 + (**format - '0');
		(*format)++;
	}
	if (flags->dot)
		flags->prec = number;
	else
		flags->width = number;
	if (flags->minus)
		flags->zero = 0;
}

static int	ft_dispatch_format(char format, va_list args, t_flags *flags)
{
	if (format == 'c')
		return (ft_print_char(args, flags));
	else if (format == 's')
		return (ft_print_str(args, flags));
	else if (format == 'd' || format == 'i')
		return (ft_print_int(args, flags));
	else if (format == 'u')
		return (ft_print_uint(args, flags));
	else if (format == 'x' || format == 'X')
		return (ft_print_hex(args, flags, format));
	else if (format == 'p')
		return (ft_print_pointer(args, flags));
	else if (format == '%')
	{
		flags->join = &format;
		return (ft_print_char(args, flags));
	}
	return (0);
}
