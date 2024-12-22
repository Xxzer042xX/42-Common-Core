/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:45:53 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/27 02:42:24 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

/* 
 Analyzes and processes format characters.
 If a '%' is found, it calls ft_parsing to handle the corresponding argument.
 Otherwise, it writes the character and updates the total count of printed char
 */
static int	ft_subpf(const char **form, va_list args, t_flags *flags, int *tot)
{
	int	check;
	int	ret;

	if (**form == '%' && *(*form + 1))
	{
		(*form)++;
		check = ft_parsing(form, args, flags);
		if (check == -1)
			return (-1);
		*tot += check;
	}
	else
	{
		ret = write(1, *form, 1);
		if (ret == -1)
			return (-1);
		*tot += ret;
	}
	return (0);
}

/* 
 * ft_printf - Implements the printf function.
 * Iterates through the format string and processes each character with ft_subpf.
 * Returns the total number of printed characters or -1 in case of an error.
 */
int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flags;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (ft_subpf(&format, args, &flags, &count) == -1)
			return (va_end(args), -1);
		format++;
	}
	return (va_end(args), count);
}
