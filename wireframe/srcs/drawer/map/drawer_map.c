/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:30:00 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/10 21:38:44 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/fdf.h"

static void	draw_horizontal_lines(t_app *app, int y);
static void	draw_vertical_lines(t_app *app, int y);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction principale gère le rendu de la carte en fil de fer        */
/*   (wireframe) en dessinant le maillage complet ligne par ligne.            */
/*                                                                            */
/*   Processus de rendu :                                                     */
/*   1. Parcourt chaque ligne verticale (y) de la carte                       */
/*   2. Pour chaque ligne :                                                   */
/*      - Dessine les connexions horizontales (points adjacents)              */
/*      - Dessine les connexions verticales (avec la ligne suivante)          */
/*                                                                            */
/*   Note : Le rendu utilise les transformations matricielles actuelles       */
/*   (projection, rotation, échelle) stockées dans app->matrix                */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale contenant :                */
/*          * Les dimensions de la carte (w_map, h_map)                       */
/*          * Les points et leurs propriétés                                  */
/*          * Les paramètres de transformation                                */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	draw_map(t_app *app)
{
	int	current_y;

	current_y = 0;
	while (current_y < app->map.h_map)
	{
		draw_horizontal_lines(app, current_y);
		draw_vertical_lines(app, current_y);
		current_y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction dessine toutes les connexions horizontales d'une ligne    */
/*   de la carte, créant les segments est-ouest du maillage.                  */
/*                                                                            */
/*   Pour chaque point de la ligne (sauf le dernier) :                        */
/*   1. Obtient les coordonnées transformées du point courant via matrix()    */
/*   2. Obtient les coordonnées transformées du point suivant                 */
/*   3. Trace une ligne entre ces deux points avec draw_line                  */
/*                                                                            */
/*   Note : Les coordonnées sont déjà transformées (projection, rotation,     */
/*   échelle) par la fonction matrix() avant le tracé.                        */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - y : index de la ligne à traiter (coordonnée verticale)                 */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	draw_horizontal_lines(t_app *app, int y)
{
	t_point	current_point;
	t_point	next_point;
	int		current_x;

	current_x = 0;
	while (current_x < app->map.w_map - 1)
	{
		current_point = matrix(app, current_x, y);
		next_point = matrix(app, current_x + 1, y);
		draw_line(app, current_point, next_point);
		current_x++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction dessine toutes les connexions verticales d'une ligne      */
/*   de la carte, créant les segments nord-sud du maillage.                   */
/*                                                                            */
/*   Pour chaque point de la ligne (sauf la dernière ligne) :                 */
/*   1. Obtient les coordonnées transformées du point courant via matrix()    */
/*   2. Obtient les coordonnées transformées du point de la ligne suivante    */
/*   3. Trace une ligne entre ces deux points avec draw_line                  */
/*                                                                            */
/*   Particularités :                                                         */
/*   - Vérifie qu'on n'est pas sur la dernière ligne (y < h_map - 1)          */
/*   - Utilise les mêmes transformations que les lignes horizontales          */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - y : index de la ligne à traiter (coordonnée verticale)                 */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	draw_vertical_lines(t_app *app, int y)
{
	t_point	current_point;
	t_point	next_point;
	int		current_x;

	current_x = 0;
	while (current_x < app->map.w_map)
	{
		if (y < app->map.h_map - 1)
		{
			current_point = matrix(app, current_x, y);
			next_point = matrix(app, current_x, y + 1);
			draw_line(app, current_point, next_point);
		}
		current_x++;
	}
}
