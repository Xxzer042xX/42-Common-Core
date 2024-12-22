/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:32:34 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/27 02:12:35 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"

static int	ft_print_pointer_sub(va_list args, t_flags *flags, char *ptr);

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
