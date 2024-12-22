/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:42:23 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/17 18:55:14 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // Inclure ta libft pour ft_putchar, ft_strlen, etc.

static int	ft_numlen_b(unsigned long long num, int base)
{
	int	len;

	len = 1;
	while (num >= (unsigned long long)base)
	{
		num /= base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(unsigned long long value, int base, int is_upper)
{
	char				*str;
	const char			*digits;
	int					len;

	if (base < 2 || base > 16)
		return (NULL);
	if (is_upper)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	len = ft_numlen_b(value, base);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[--len] = digits[value % base];
		value /= base;
	}
	return (str);
}
