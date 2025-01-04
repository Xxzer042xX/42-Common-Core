/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:08:58 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/25 13:08:58 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Fonction de tri pour les piles de grande taille.                         */
/*                                                                            */
/*   Implémente un algorithme de tri radix en base 2 (tri binaire) :          */
/*   1. Calcule le nombre de bits nécessaires pour représenter les indices    */
/*   2. Pour chaque bit (du moins significatif au plus significatif) :        */
/*      - Si le bit est 0 : déplace le nombre vers la pile B (pb)             */
/*      - Si le bit est 1 : rotate la pile A (ra)                             */
/*   3. Après chaque bit, ramène tous les nombres de B vers A (pa)            */
/*                                                                            */
/*   Complexité :                                                             */
/*   - Temporelle : O(n * max_bits) où n est le nombre d'éléments             */
/*   - Spatiale : O(1) car utilise uniquement les piles existantes            */
/*                                                                            */
/*   Paramètres :                                                             */
/*   - a : pointeur vers la pile principale A                                 */
/*   - b : pointeur vers la pile auxiliaire B                                 */
/*                                                                            */
/*   Fonctionnement détaillé :                                                */
/*   - Utilise les indices préalablement assignés aux nombres                 */
/*   - Trie bit par bit en utilisant l'opérateur de décalage (>>)             */
/*   - L'opération & 1 permet d'isoler le bit actuel                          */
/*   - Le processus est répété pour chaque position de bit                    */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	sort_big(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	i;
	int	j;
	int	size;

	size = a->size;
	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if (!(a->first_node->index >> i & 1))
				pb(a, b);
			else
				ra(a);
			j++;
		}
		while (b->size > 0)
			pa(a, b);
		i++;
	}
}
