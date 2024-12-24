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

static int	ft_get_digit_value(const char c, int base);
static int	ft_atoi_base_process(const char *nptr, int base);

int	ft_atoi_base(const char *nptr, int base)
{
	int	sign;
	int	result;

	if (!nptr || base < 2 || base > 16)
		return (0);
	result = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (base == 16 && nptr[0] == '0' && (nptr[1] == 'x' || nptr[1] == 'X'))
		nptr += 2;
	result = ft_atoi_base_process(nptr, base);
	if (result == -1)
		return (-1);
	return (sign * result);
}

static int	ft_atoi_base_process(const char *nptr, int base)
{
	int	digit;
	int	result;

	result = 0;
	while (*nptr)
	{
		digit = ft_get_digit_value(*nptr, base);
		if (digit == -1)
			break ;
		result = (result * base) + digit;
		nptr++;
	}
	return (result);
}

static int	ft_get_digit_value(const char c, int base)
{
	int	digit;

	if (c >= '0' && c <= '9')
		digit = c - '0';
	else if (c >= 'a' && c <= 'f')
		digit = c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		digit = c - 'A' + 10;
	else
		return (-1);
	if (digit >= base)
		return (-1);
	return (digit);
}
