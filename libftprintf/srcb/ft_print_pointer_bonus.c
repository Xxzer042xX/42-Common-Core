/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:32:34 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/27 02:12:35 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"
#include "../libft/libft.h"

static int	ft_print_pointer_sub(va_list args, t_flags *flags, char *ptr);

/*
 Prints a pointer in hexadecimal format with formatting.
 Retrieves a pointer from args. If NULL, sets flags and calls ft_print_str to
 handle null pointer output. Otherwise, calls ft_print_pointer_sub
 for hex conversion.
 */
int	ft_print_pointer(va_list args, t_flags *flags)
{
	void	*ptr;

	ptr = va_arg(args, void *);
	if (!ptr)
	{
		flags->join = NULL_POINTER;
		flags->is_null = 1;
		return (ft_print_str(args, flags));
	}
	return (ft_print_pointer_sub(args, flags, ptr));
}

/*
 Converts pointer to hex and formats for printing.
 Converts 'ptr' to a hexadecimal string with "0x" prefix. Manages memory alloc
 for the formatted string and calls ft_print_str to print it.
 */
static int	ft_print_pointer_sub(va_list args, t_flags *flags, char *ptr)
{
	char	*s2;
	char	*join;
	int		count;

	s2 = ft_itoa_base((unsigned long long)ptr, 16, 0);
	if (!s2)
		return (-1);
	join = (char *)malloc(sizeof(char) * (ft_strlen(s2) + 3));
	if (!join)
		return (free(s2), -1);
	join[0] = '0';
	join[1] = 'x';
	ft_strlcpy(join + 2, s2, ft_strlen(s2) + 1);
	flags->join = join;
	if (!flags->join)
		return (free(join), free(s2), -1);
	count = ft_print_str(args, flags);
	return (free(join), free(s2), count);
}
