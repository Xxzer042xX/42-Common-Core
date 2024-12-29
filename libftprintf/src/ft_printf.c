/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:45:53 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/27 02:42:24 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

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

//main function that will call the other functions
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
