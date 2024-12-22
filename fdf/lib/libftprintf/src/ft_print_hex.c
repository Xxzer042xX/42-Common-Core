/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:05:02 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/31 19:18:26 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"

static int	ft_prefix(t_flags *flags, char spec, unsigned int n);

int	ft_print_hex(va_list args, t_flags *flags, char specifier)
{
	unsigned int	n;
	char			*str;

	n = va_arg(args, unsigned int);
	if (specifier == 'x')
		str = ft_itoa_base(n, 16, 0);
	else
		str = ft_itoa_base(n, 16, 1);
	if (!str)
		return (-1);
	flags->join = str;
	flags->is_uintx = 1;
	if (ft_prefix(flags, specifier, n) == -1)
		return (free(str), -1);
	return (ft_print_int(args, flags));
}

static int	ft_prefix(t_flags *flags, char spec, unsigned int n)
{
	char	*join;

	join = NULL;
	if (flags->hash && n != 0)
	{
		join = (char *)malloc(sizeof(char) * (ft_strlen(flags->join) + 3));
		if (!join)
			return (-1);
		join[0] = '0';
		if (spec == 'x')
			join[1] = 'x';
		else if (spec == 'X')
			join[1] = 'X';
		ft_strlcpy(join + 2, flags->join, ft_strlen(flags->join) + 1);
		free(flags->join);
		flags->join = join;
		if (!flags->join)
			return (free(join), -1);
	}
	return (0);
}
