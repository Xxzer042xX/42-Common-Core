/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ishexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:02:17 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/08 15:31:37 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ishexa(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!((ft_isdigit(str[i]) || (str[i] >= 'a' && str[i] <= 'f') || \
			(str[i] >= 'A' && str[i] <= 'F'))))
			return (0);
		i++;
	}
	return (1);
}
