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

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'analyse et de traitement des arguments du programme.          */
/*                                                                            */
/*   Cette fonction gère deux formats d'entrée possibles :                    */
/*   1. Un seul argument contenant tous les nombres séparés par des espaces   */
/*   2. Plusieurs arguments, chacun contenant un seul nombre                  */
/*                                                                            */
/*   Dans le cas d'un seul argument :                                         */
/*   - Découpe la chaîne en utilisant les espaces comme séparateurs           */
/*   - Traite chaque nombre individuellement                                  */
/*   - Libère la mémoire allouée pour le découpage                            */
/*                                                                            */
/*   Dans le cas de plusieurs arguments :                                     */
/*   - Vérifie que chaque argument n'est pas vide                             */
/*   - Traite chaque argument comme un nombre                                 */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - ac : nombre d'arguments                                                */
/*   - av : tableau des arguments                                             */
/*   - stack : pointeur vers la pile à remplir                                */
/*                                                                            */
/*   Retourne :                                                               */
/*   - SUCCESS : si tous les arguments ont été traités avec succès            */
/*   - ERR_MALLOC : si l'allocation mémoire échoue                            */
/*   - ERR_ARGS : si un argument est invalide                                 */
/*   - Autres codes d'erreur possibles selon process_number                   */
/*                                                                            */
/* ************************************************************************** */
int	parse_args(int ac, char **av, t_stack *stack)
{
	char	**numbers;
	int		i;
	int		status;

	i = 0;
	if (ac == 1)
	{
		numbers = ft_split(av[0], ' ');
		if (!numbers)
			return (ERR_MALLOC);
		status = handle_numbers(stack, numbers);
		ft_free_split(numbers, 0);
		return (status);
	}
	while (i < ac)
	{
		status = process_number(stack, av[i]);
		if (status != SUCCESS)
			return (status);
		i++;
	}
	return (SUCCESS);
}
