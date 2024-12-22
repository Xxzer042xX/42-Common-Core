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

#include "../include/ft_printf_bonus.h"
#include "../libft/libft.h"

static int	ft_dispatch_format(char format, va_list args, t_flags *flags);
static void	ft_parse_number(const char **format, t_flags *flags);
static void	ft_set_flag(const char **format, t_flags *flags);

/*
 Parses the format string to extract flags, width, precision, and specifiers.
 initializes the flags structure and processes each character
 in the format string.
 Calls respective functions for setting flags, parsing numbers,
 and handling specifiers.
 */
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

/*
 Sets the flags in the flags structure based on the current format character.
 Handles various flags like '-', '0', '#', '+', ' ', and '.'.
 Increments the format pointer to move to the next character.
 */
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

/*
 Parses numeric values in the format string 
 for width or precision.
 Updates the width or precision field in the flags structure.
 Adjusts the zero flag if the minus flag is set (cannot have both).
 */
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

/*
 Dispatches the format specifier to 
 the corresponding print function.
 Handles specifiers for characters, strings, integers, unsigned integers,
 hexadecimals, and pointers.
 Returns the result of the corresponding print function or
 directly writes the character if unrecognized.
 */
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
	return (write(1, &format, 1));
}
