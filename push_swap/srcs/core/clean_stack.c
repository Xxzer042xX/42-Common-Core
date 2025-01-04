/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:34:03 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/01 19:34:03 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	free_stack(t_stack *stack);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de nettoyage final du programme.                                */
/*                                                                            */
/*   Cette fonction se charge de libérer proprement toute la mémoire          */
/*   allouée pour les piles A et B, et affiche un message d'erreur si         */
/*   nécessaire avant la fin du programme.                                    */
/*                                                                            */
/*   Actions effectuées :                                                     */
/*   1. Libération de la pile A si elle existe                                */
/*   2. Libération de la pile B si elle existe                                */
/*   3. Affichage du message d'erreur si le statut n'est pas SUCCESS          */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile A                                            */
/*   - b : pointeur vers la pile B                                            */
/*   - status : code de statut/erreur du programme                            */
/*                                                                            */
/*   Retourne  le status de fin du programme                                  */
/*                                                                            */
/* ************************************************************************** */
int	cleanup(t_stack *a, t_stack *b, int status)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	if (status != SUCCESS)
		print_error(status);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction utilitaire pour libérer la mémoire d'une pile complète.         */
/*                                                                            */
/*   Cette fonction statique libère récursivement tous les noeuds d'une       */
/*   pile ainsi que la structure de la pile elle-même.                        */
/*                                                                            */
/*   Processus de libération :                                                */
/*   1. Vérification de l'existence de la pile                                */
/*   2. Parcours de tous les noeuds de la pile                                */
/*   3. Libération de chaque noeud individuellement                           */
/*   4. Libération finale de la structure de pile                             */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile à libérer                                */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	current = stack->first_node;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(stack);
}
