/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_random_number.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:41:36 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/02 13:41:36 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void generate_unique_number(long long *used, int *result, int index) {
    long long range = (long long)INT_MAX - (long long)INT_MIN;
    long long random_num;
    int found = 0;
    
    while (!found) {
        // Générer un nombre sur toute la plage INT
        random_num = (long long)rand() * (long long)rand();
        random_num = (random_num % range) + INT_MIN;
        
        // Vérifier si le nombre a déjà été utilisé
        long long array_index = random_num - INT_MIN;
        if (used[array_index] == 0) {
            used[array_index] = 1;
            result[index] = (int)random_num;
            found = 1;
        }
    }
}

int main(int ac, char **av)
{
    const int COUNT = atoi(av[1]);
    int result[COUNT];
    // Tableau pour suivre les nombres utilisés
    long long *used = (long long *)calloc((long long)INT_MAX - (long long)INT_MIN + 1, sizeof(long long));
    
    if (used == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return 1;
    }
    
    srand(time(NULL));
    
    // Générer COUNT nombres uniques
    for (int i = 0; i < COUNT; i++) {
        generate_unique_number(used, result, i);
    }
    
    // Imprimer la commande formatée
    printf("ARG=\"");
    for (int i = 0; i < COUNT; i++) {
        printf("%d", result[i]);
        if (i < COUNT - 1)
            printf(" ");
    }
    printf("\"; ./bin/push_swap $ARG | ./tools/checker_linux $ARG\n");
    
    free(used);
    return 0;
}