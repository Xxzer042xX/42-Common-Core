/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:35:09 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/18 20:10:28 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction détermine la hauteur de la carte en comptant les          */
/*   lignes non vides du fichier FdF.                                         */
/*                                                                            */
/*   Processus de comptage :                                                  */
/*   1. Ouverture du fichier en lecture seule                                 */
/*   2. Lecture séquentielle avec get_next_line :                             */
/*      - Ignore les lignes vides (contenant uniquement '\n')                 */
/*      - Incrémente le compteur pour les lignes valides                      */
/*   3. Libération de la mémoire après chaque ligne                           */
/*   4. Fermeture du fichier                                                  */
/*   5. Stockage de la hauteur dans app->map.h_map                            */
/*                                                                            */
/*   Vérifications :                                                          */
/*   - S'assure que le fichier contient au moins une ligne valide             */
/*   - Gère la libération mémoire pour chaque ligne lue                       */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale contenant                  */
/*          la sous-structure map pour stocker la hauteur                     */
/*   - filename : chemin du fichier FdF à analyser                            */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si au moins une ligne valide est trouvée                       */
/*   - ERR_FILE si :                                                          */
/*     * Le fichier est vide                                                  */
/*     * Ne contient que des lignes vides                                     */
/*                                                                            */
/* ************************************************************************** */
int	count_line(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (count == 0)
		return (0);
	return (count);
}
