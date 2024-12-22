/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:12:35 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/18 20:17:47 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction initialise la structure de la carte (map) à partir d'un   */
/*   fichier FdF en trois étapes :                                            */
/*                                                                            */
/*   1. count_line :                                                          */
/*      - Compte le nombre de lignes dans le fichier                          */
/*      - Stocke la hauteur dans app->map.h_map                               */
/*      - Vérifie la validité du fichier                                      */
/*                                                                            */
/*   2. Allocation mémoire :                                                  */
/*      - Alloue un tableau de pointeurs de taille h_map                      */
/*      - Chaque pointeur représentera une ligne de la carte                  */
/*                                                                            */
/*   3. parse_file :                                                          */
/*      - Parse le contenu complet du fichier                                 */
/*      - Remplit la structure points avec les coordonnées et couleurs        */
/*                                                                            */
/*   La fonction vérifie chaque étape et retourne immédiatement en cas        */
/*   d'erreur.                                                                */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale contenant                  */
/*          la sous-structure map pour les données de la carte                */
/*   - filename : chemin du fichier FdF à parser                              */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si l'initialisation complète réussit                           */
/*   - ERR_FILE si :                                                          */
/*     * Le comptage des lignes échoue                                        */
/*     * Le parsing du fichier échoue                                         */
/*   - ERR_MALLOC si l'allocation du tableau de points échoue                 */
/*                                                                            */
/* ************************************************************************** */
int	init_map(t_app *app, char *filename)
{
	int	count;

	count = count_line(filename);
	if (count <= 0)
		return (ERR_FILE);
	app->map.h_map = count;
	app->map.points = malloc(sizeof(t_point *) * app->map.h_map);
	if (!app->map.points)
		return (ERR_MALLOC);
	ft_memset(app->map.points, 0, sizeof(t_point *) * app->map.h_map);
	if (parse_file(app, filename) != SUCCESS)
		return (ERR_FILE);
	return (SUCCESS);
}
