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

void	generate_unique_number(long long *used, int *result, int index)
{
	long long	array_index;
	long long	random_num;
	int			found;

	found = 0;
	while (!found)
	{
		// Générer un nombre uniforme entre INT_MIN et INT_MAX
		random_num = ((long long)rand() * RAND_MAX + rand()) % ((long long)INT_MAX - (long long)INT_MIN + 1) + INT_MIN;
		array_index = random_num - INT_MIN;
		if (used[array_index] == 0)
		{
			used[array_index] = 1;
			result[index] = (int)random_num;
			found = 1;
		}
	}
}

int	main(int ac, char **av)
{
	int			i;
	int			count;
	int			*result;
	long long	*used;

	if (ac != 2)
	{
		printf("Usage: %s <count>\n", av[0]);
		return (1);
	}
	
	count = atoi(av[1]);
	if (count <= 0)
	{
		printf("Le nombre d'éléments doit être positif.\n");
		return (1);
	}

	result = (int *)malloc(count * sizeof(int));
	if (result == NULL)
	{
		printf("Erreur d'allocation mémoire pour 'result'.\n");
		return (1);
	}

	used = (long long *)calloc((long long)INT_MAX - (long long)INT_MIN + 1, sizeof(long long));
	if (used == NULL)
	{
		printf("Erreur d'allocation mémoire pour 'used'.\n");
		free(result);
		return (1);
	}

	srand(time(NULL));
	i = 0;
	while (i < count)
	{
		generate_unique_number(used, result, i++);
	}

	printf("ARG=\"");
	i = 0;
	while (i < count)
	{
		printf("%d", result[i]);
		if (i < count - 1)
			printf(" ");
		i++;
	}
	printf("\"; ./bin/push_swap $ARG | ./tools/checker_linux $ARG\n");

	free(result);
	free(used);
	return (0);
}

