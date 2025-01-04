/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:43:02 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/01 19:43:02 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction d'initialisation d'une nouvelle pile pour le programme.         */
/*                                                                            */
/*   Cette fonction alloue dynamiquement la mémoire nécessaire pour une       */
/*   nouvelle pile et l'initialise avec des valeurs par défaut.               */
/*                                                                            */
/*   Étapes d'initialisation :                                                */
/*   1. Allocation de la mémoire pour la structure de la pile                 */
/*   2. Vérification de la réussite de l'allocation                           */
/*   3. Mise à zéro de toute la zone mémoire allouée                          */
/*   4. Attribution de l'identifiant de la pile                               */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - id : caractère identifiant la pile ('a' ou 'b')                        */
/*   - stack : pointeur vers le pointeur de la pile à initialiser             */
/*                                                                            */
/*   Retourne :                                                               */
/*   - SUCCESS : si l'initialisation s'est bien déroulée                      */
/*   - ERR_MALLOC : en cas d'échec de l'allocation mémoire                    */
/*                                                                            */
/* ************************************************************************** */
int	init_stack(char id, t_stack **stack)
{
	*stack = malloc(sizeof(t_stack));
	if (!*stack)
		return (ERR_MALLOC);
	ft_memset(*stack, 0, sizeof(t_stack));
	(*stack)->id_stack = id;
	return (SUCCESS);
}
