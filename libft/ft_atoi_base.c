/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:02:09 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/08 15:22:48 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_digit_value(char c, int base)
{
	char	*charset;
	int		i;

	charset = "0123456789abcdefABCDEF";
	i = 0;
	while (charset[i] && charset[i] != c)
		i++;
	if (i >= 16)
		i -= 6;
	if (i >= base)
		return (-1);
	return (i);
}

int	ft_atoi_base_process(const char *str, int base)
{
	int	digit;
	int	result;

	result = 0;
	while (*str)
	{
		digit = ft_get_digit_value(*str, base);
		if (digit == -1)
			break ;
		result = (result * base) + digit;
		str++;
	}
	return (result);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;

	if (!str || base < 2 || base > 16)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (base == 16 && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	result = ft_atoi_base_process(str, base);
	return (sign * result);
}

