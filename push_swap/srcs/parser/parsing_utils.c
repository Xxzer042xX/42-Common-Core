/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:55:17 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/31 21:55:17 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

static int	convert_to_int(const char *str, int *num);
static int	check_duplicate(t_stack *stack, int num);
static int	add_to_stack(t_stack *stack, int num);

/* ************************************************************************** */
/*                                                                            */
/*   Fonction principale de traitement des nombres pour la pile.              */
/*                                                                            */
/*   Parcourt un tableau de chaînes de caractères contenant des nombres et    */
/*   les traite un par un pour les ajouter à la pile.                         */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile à remplir                                */
/*   - numbers : tableau de chaînes contenant les nombres à traiter           */
/*                                                                            */
/*   Retourne :                                                               */
/*   - SUCCESS : si tous les nombres ont été traités avec succès              */
/*   - Code d'erreur approprié si une erreur survient                         */
/*                                                                            */
/* ************************************************************************** */
int	handle_numbers(t_stack *stack, char **numbers)
{
	int	i;
	int	status;

	i = 0;
	while (numbers && numbers[i])
	{
		status = process_number(stack, numbers[i]);
		if (status != SUCCESS)
			return (status);
		i++;
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de traitement d'un nombre individuel.                           */
/*                                                                            */
/*   Coordonne les trois étapes de validation et d'ajout d'un nombre :        */
/*   1. Conversion de la chaîne en entier                                     */
/*   2. Vérification des doublons                                             */
/*   3. Ajout à la pile                                                       */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile                                          */
/*   - str : chaîne de caractères représentant le nombre                      */
/*                                                                            */
/*   Retourne :                                                               */
/*   - SUCCESS : si le nombre est valide et a été ajouté                      */
/*   - Code d'erreur approprié sinon                                          */
/*                                                                            */
/* ************************************************************************** */
int	process_number(t_stack *stack, const char *str)
{
	int	num;

	if (convert_to_int(str, &num) != SUCCESS)
		return (ERR_ARGS);
	if (check_duplicate(stack, num) != SUCCESS)
		return (ERR_DUP);
	return (add_to_stack(stack, num));
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction utilitaire de conversion d'une chaîne en entier.                */
/*                                                                            */
/*   Vérifie la validité de la chaîne et la convertit en entier :             */
/*   1. Gestion du signe négatif                                              */
/*   2. Vérification que tous les caractères sont des chiffres                */
/*   3. Conversion et vérification des limites MIN_INT et MAX_INT             */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - str : chaîne à convertir                                               */
/*   - num : pointeur vers l'entier qui recevra la valeur                     */
/*                                                                            */
/*   Retourne :                                                               */
/*   - SUCCESS : si la conversion est réussie                                 */
/*   - ERR_ARGS : si la chaîne est invalide ou hors limites                   */
/*                                                                            */
/* ************************************************************************** */
static int	convert_to_int(const char *str, int *num)
{
	long	result;
	int		i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (!str[i])
		return (ERR_ARGS);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (ERR_ARGS);
		i++;
	}
	result = ft_atol(str);
	if (result > MAX_INT || result < MIN_INT)
		return (ERR_ARGS);
	*num = (int)result;
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction utilitaire de vérification des doublons.                        */
/*                                                                            */
/*   Parcourt la pile pour vérifier si le nombre existe déjà :                */
/*   1. Vérification de l'existence de la pile                                */
/*   2. Parcours de tous les noeuds                                           */
/*   3. Comparaison avec la valeur recherchée                                 */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile                                          */
/*   - num : nombre à vérifier                                                */
/*                                                                            */
/*   Retourne :                                                               */
/*   - SUCCESS : si le nombre n'existe pas dans la pile                       */
/*   - ERR_DUP : si le nombre est déjà présent                                */
/*                                                                            */
/* ************************************************************************** */
static int	check_duplicate(t_stack *stack, int num)
{
	t_node	*current;

	current = stack->first_node;
	while (current)
	{
		if (current->value == num)
			return (ERR_DUP);
		current = current->next;
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*   Fonction utilitaire d'ajout d'un nombre à la pile.                       */
/*                                                                            */
/*   Crée un nouveau noeud et l'ajoute à la fin de la pile :                  */
/*   1. Allocation du nouveau noeud                                           */
/*   2. Initialisation des valeurs                                            */
/*   3. Mise à jour des pointeurs (cas pile vide et non vide)                 */
/*   4. Mise à jour de la taille de la pile                                   */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - stack : pointeur vers la pile                                          */
/*   - num : nombre à ajouter                                                 */
/*                                                                            */
/*   Retourne :                                                               */
/*   - SUCCESS : si l'ajout est réussi                                        */
/*   - ERR_MALLOC : si l'allocation échoue                                    */
/*   - ERR_ARGS : si la pile n'existe pas                                     */
/*                                                                            */
/* ************************************************************************** */
static int	add_to_stack(t_stack *stack, int num)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (ERR_MALLOC);
	ft_memset(new, 0, sizeof(t_node));
	new->value = num;
	if (!stack->first_node)
	{
		stack->first_node = new;
		stack->last_node = new;
	}
	else
	{
		new->prev = stack->last_node;
		stack->last_node->next = new;
		stack->last_node = new;
	}
	stack->size++;
	return (SUCCESS);
}
