/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generathor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:07:42 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/13 14:07:42 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libftprintf/include/ft_printf.h"
#include "../../lib/libftprintf/libft/libft.h"
/*
static void	generate_map(int row, int col, int fp);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction principale gère la création d'une carte FdF plate.        */
/*   Elle vérifie les arguments, ouvre le fichier destination et appelle      */
/*   la fonction de génération.                                               */
/*                                                                            */
/*   Paramètres attendus :                                                    */
/*   ./generathor colonnes lignes fichier_destination                         */
/*                                                                            */
/*   Retourne:                                                                */
/*   - 0 en cas de succès                                                     */
/*   - 1 si nombre d'arguments incorrect ou erreur d'ouverture fichier        */
/*                                                                            */
/* ************************************************************************** */
/*
int	main(int ac, char **av)
{
	int		fd;
	int		i;
	int		j;
	int		col;
	int		row;

	if (ac != 3)
	{
		ft_printf("Usage: ./generathor [col] [row] \n");
		return (1);
	}
	col = ft_atoi(av[1]);
	row = ft_atoi(av[2]);
	fd = open("flat.fdf", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	generate_map(row, col, fd);
	close(fd);
	return (0);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction génère une carte FdF plate composée uniquement de         */
/*   points d'altitude zéro.                                                  */
/*                                                                            */
/*   Format de sortie :                                                       */
/*   - Points séparés par des espaces sur chaque ligne                        */
/*   - Lignes séparées par des retours à la ligne                             */
/*   - Pas d'espace superflu en fin de ligne                                  */
/*   - Pas de retour à la ligne après la dernière ligne                       */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - row : nombre de lignes à générer                                       */
/*   - col : nombre de colonnes par ligne                                     */
/*   - fd : descripteur du fichier de sortie                                  */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
/*
static void	generate_map(int row, int col, int fd)
{
	int	i;
	int	j;

	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			if (j < col - 1)
				ft_putstr_fd("0 ", fd);
			else
				ft_putstr_fd("0", fd);
			j++;
		}
		if (i < row - 1)
			ft_putstr_fd("\n", fd);
		i++;
	}
}

/*void    put_zero(int row, int col, FILE *fp)
{
    int        i;
    int        j;

    i = 0;
    while (i < row)
    {
        j = 0;
        while (j < col)
        {
            if (j < col - 1)
            {    
                if (j % 2 == 0)
                    fprintf(fp, "10 ");
                else if (j % 3 == 0)
                    fprintf(fp, "20 ");
                else if (j % 5 == 0)
                    fprintf(fp, "30 ");
                else
                    fprintf(fp, "0 ");
            }
            else
                fprintf(fp, "0");
            j++;
        }
        if (i < row - 1)
            fprintf(fp, "\n");
        i++;
    }
}
*/

static void generate_map(int row, int col, int fd)
{
    int i;
    int j;
    int crevasse_start;
    int height;
    char buffer[20];  // Buffer pour convertir les nombres en chaînes

    // Initialisation de i
    i = 0;
    // Position de la crevasse (au milieu de la carte)
    crevasse_start = col / 3;
    
    while (i < row)
    {
        j = 0;
        while (j < col)
        {
            // Création de la crevasse
            if (j >= crevasse_start && j <= (crevasse_start + 50))
            {
                // Profondeur variable de la crevasse (-80 à -100)
                height = -80 - (rand() % 21);
            }
            else
            {
                // Surface accidentée (-5 à 5)
                height = (rand() % 11) - 5;
                
                // Transition vers la crevasse
                if (j == crevasse_start - 1 || j == crevasse_start + 51)
                    height = -20 - (rand() % 21); // -20 à -40
                else if (j == crevasse_start - 2 || j == crevasse_start + 52)
                    height = -10 - (rand() % 11); // -10 à -20
            }

            // Conversion du nombre en chaîne
            ft_itoa_base(height, buffer); // Vous devrez implémenter cette fonction ou utiliser ft_itoa

            // Écriture dans le fichier
            if (j < col - 1)
            {
                ft_putstr_fd(buffer, fd);
                ft_putchar_fd(' ', fd);
            }
            else
                ft_putstr_fd(buffer, fd);
            j++;
        }
        if (i < row - 1)
            ft_putchar_fd('\n', fd);
        i++;
    }
}

int main(int ac, char **av)
{
    int fd;

    if (ac > 1)  // Changé pour vérifier si des arguments sont passés
    {
        ft_printf("Usage: ./generathor\n");
        return (1);
    }

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));
    
    fd = open("ice_crevasse.fdf", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (1);

    // Génération d'une carte 500x50
    generate_map(50, 500, fd);
    close(fd);
    return (0);
}