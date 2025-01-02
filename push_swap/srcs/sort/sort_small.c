/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:55:56 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/01 23:55:56 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

static void	get_three_values(t_stack *a, int *first, int *second, int *third)
{
    *first = a->first_node->value;
    *second = a->first_node->next->value;
    *third = a->last_node->value;
}

static void rotate_to_min(t_stack *a)
{
    if (!a || !a->first_node || a->size < 2)
        return;

    int min_pos = find_min_pos(a);
    
    // Vérifie que min_pos est valide
    if (min_pos < 0 || min_pos >= a->size)
        return;

    while (min_pos > 0)
    {
        if (min_pos <= a->size / 2)
        {
            ra(a);
            min_pos--;
        }
        else
        {
            rra(a);
            min_pos = (min_pos + 1) % a->size;
        }
    }
}

void	sort_three(t_stack *a)
{
    int	first;
    int	second;
    int	third;

    if (a->size != 3)
        return ;
    get_three_values(a, &first, &second, &third);
    if (first > second && second < third && first < third)
        sa(a);
    else if (first > second && second > third)
    {
        sa(a);
        rra(a);
    }
    else if (first > second && second < third && first > third)
        ra(a);
    else if (first < second && second > third && first < third)
    {
        sa(a);
        ra(a);
    }
    else if (first < second && second > third && first > third)
        rra(a);
}

void sort_four(t_stack *a, t_stack *b)
{
    if (!a || !b || !a->first_node)
        return;

    // Vérifie que nous avons bien 4 éléments
    if (a->size != 4)
        return;

    // Déplace le plus petit élément
    rotate_to_min(a);
    if (a->size > 3)
        pb(a, b);

    // Vérifie que nous avons bien 3 éléments avant de trier
    if (a->size == 3)
        sort_three(a);

    // Ramène l'élément de b
    if (b && b->size > 0)
        pa(a, b);
}

void sort_five(t_stack *a, t_stack *b)
{
    // Vérifications de base
    if (!a || !b || !a->first_node)
        return;

    // Vérifie que nous avons bien 5 éléments
    if (a->size != 5)
        return;

    // Stocke la taille initiale
    int initial_size = a->size;
    
    // Déplace les 2 plus petits éléments vers b
    while (a->size > 3 && initial_size == 5)
    {
        if (!a->first_node) // Protection supplémentaire
            break;
            
        rotate_to_min(a);
        if (b && a->size > 3)
            pb(a, b);
    }

    // Vérifie que nous avons bien 3 éléments avant de trier
    if (a->size == 3)
        sort_three(a);

    // Ramène les éléments de b vers a
    while (b && b->size > 0)
        pa(a, b);
}