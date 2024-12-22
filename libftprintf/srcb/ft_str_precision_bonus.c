/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_prec_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:39:48 by madelmen          #+#    #+#             */
/*   Updated: 2024/10/28 20:36:58 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

/*
 Prints up to 'prec' characters of the given string.
 Iterates through the string, printing each character until 'prec' characters
 are printed.
 */
int	ft_print_str_prec(char *str, int prec)
{
	int	i;
	int	char_count;

	i = 0;
	char_count = 0;
	while (i < prec)
	{
		if (write(1, &str[i], 1) == -1)
			return (-1);
		char_count++;
		i++;
	}
	return (char_count);
}
