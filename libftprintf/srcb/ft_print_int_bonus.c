/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:32:13 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/06 14:43:19 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"
#include "../libft/libft.h"

static int	ft_proces_int(t_flags *flags, int to_print, int *n);
static void	ft_is_nega(t_flags *flags, int *n);

/*
 ft_print_int - Prints an integer with formatting.
 Retrieves an integer from args, converts it to a string, and applies
 flags for negative handling. Calls ft_proces_int to manage width,
 padding, and alignment.
 */
int	ft_print_int(va_list args, t_flags *flags)
{
	char	*str;
	int		str_len;
	int		n;

	if (flags->join)
		str = flags->join;
	else
	{
		n = va_arg(args, int);
		if (n < 0)
			ft_is_nega(flags, &n);
		str = ft_itoa(n);
	}
	if (!str)
		return (-1);
	str_len = ft_strlen(str);
	n = 0;
	flags->join = str;
	if (ft_proces_int(flags, str_len, &n) == -1)
		return (free(str), -1);
	return (free(str), n);
}

/*
 ft_is_nega - Adjusts flags and integer value for negative numbers.
 Sets the is_nega flag and makes the integer positive for processing,
 unless it’s the smallest integer, in which case a special flag is set.
 */
static void	ft_is_nega(t_flags *flags, int *n)
{
	if (*n != -2147483648)
	{
		*n *= -1;
		flags->is_nega = 1;
	}
	else
		flags->is_nega = -1;
}

/*
 Processes integer printing with width, padding, and alignment.
 Applies flags (minus, width, dot) for formatted output and calls the respective
 functions. Handles sign and writes the final output.
 */
static int	ft_proces_int(t_flags *flags, int to_print, int *n)
{
	int	result;

	if (flags->minus)
		return (ft_int_minus(flags, to_print, n));
	if (flags->width)
		return (ft_int_width(flags, to_print, n));
	if (flags->dot)
		return (ft_int_dot(flags, to_print, n));
	else
	{
		result = ft_print_sign(flags, n);
		if (result == -1)
			return (-1);
		*n += result;
		result = write(1, flags->join, to_print);
		if (result == -1)
			return (-1);
		*n += result;
		return (0);
	}
}
