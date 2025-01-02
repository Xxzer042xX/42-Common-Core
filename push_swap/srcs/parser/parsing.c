/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:40:14 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/27 17:33:56 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

int parse_args(int ac, char **av, t_stack *stack)
{
    char    **numbers;
    int     i;
    int     status;

    i = 0;
    // Si c'est un seul argument, on le split directement
    if (ac == 1)
    {
        numbers = ft_split(av[0], ' ');
        if (!numbers)
            return (ERR_MALLOC);
        status = handle_numbers(stack, numbers);
        ft_free_split(numbers, 0);
        return (status);
    }
    // Si plusieurs arguments, on les traite un par un sans split
    while (i < ac)
    {
        if (!av[i] || !av[i][0])
            return (ERR_ARGS);
        // On passe directement à handle_numbers sans split
        status = process_number(stack, av[i]);
        if (status != SUCCESS)
            return (status);
        i++;
    }
    return (SUCCESS);
}
