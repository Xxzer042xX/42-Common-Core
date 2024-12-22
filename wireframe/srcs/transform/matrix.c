/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:46:16 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/15 02:38:45 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static t_rot_point	rotate_point(double x, double y, double angle, t_app *app);
static t_rot_point	get_proj_coords(t_app *app, int grid_x, int grid_y, int z);
static void			apply_transformations(t_point *point, t_app *app);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction centrale coordonne toutes les transformations             */
/*   géométriques appliquées à un point de la grille 3D.                      */
/*                                                                            */
/*   Séquence de transformations :                                            */
/*   1. Extraction des données du point de la grille                          */
/*   2. Calcul des coordonnées dans l'espace grille                           */
/*   3. Application de la rotation autour du centre                           */
/*   4. Application de la projection selon le mode de vue                     */
/*   5. Transfert des coordonnées transformées                                */
/*   6. Application des transformations finales (zoom, décalage)              */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale contenant :                */
/*          * Les paramètres de transformation (matrix)                       */
/*          * Les points de la carte (map)                                    */
/*   - x : index horizontal dans la grille                                    */
/*   - y : index vertical dans la grille                                      */
/*                                                                            */
/*   Retourne:                                                                */
/*   - t_point avec les coordonnées finales pour l'affichage                  */
/*                                                                            */
/* ************************************************************************** */
t_point	matrix(t_app *app, int x, int y)
{
	t_point		point;
	t_rot_point	coords;
	t_rot_point	final;
	int			grid_x;
	int			grid_y;

	point = app->map.points[y][x];
	grid_x = x * app->matrix.space;
	grid_y = y * app->matrix.space;
	final = rotate_point(grid_x, grid_y, app->matrix.angle_z, app);
	coords = get_proj_coords(app, final.x, final.y, point.pos.z);
	point.pos.x = coords.x;
	point.pos.y = coords.y;
	apply_transformations(&point, app);
	return (point);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction effectue la rotation 2D d'un point autour d'un pivot      */
/*   central en utilisant une matrice de rotation standard.                   */
/*                                                                            */
/*   Algorithme de rotation :                                                 */
/*   1. Calcul du point pivot (centre de la carte)                            */
/*   2. Translation au pivot (soustraction des coordonnées pivot)             */
/*   3. Application de la matrice de rotation :                               */
/*      x' = x*cos(θ) - y*sin(θ)                                              */
/*      y' = x*sin(θ) + y*cos(θ)                                              */
/*   4. Translation inverse (addition des coordonnées pivot)                  */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - x, y : coordonnées du point à tourner                                  */
/*   - angle : angle de rotation en radians                                   */
/*   - app : pointeur vers les dimensions de la carte                         */
/*                                                                            */
/*   Retourne:                                                                */
/*   - t_rot_point avec les nouvelles coordonnées après rotation              */
/*                                                                            */
/* ************************************************************************** */
static t_rot_point	rotate_point(double x, double y, double angle, t_app *app)
{
	t_rot_point	result;
	int			pivot_x;
	int			pivot_y;
	int			dx;
	int			dy;

	pivot_x = (app->map.w_map * app->matrix.space) / 2;
	pivot_y = (app->map.h_map * app->matrix.space) / 2;
	dx = x - pivot_x;
	dy = y - pivot_y;
	result.x = pivot_x + (dx * cos(angle) - dy * sin(angle));
	result.y = pivot_y + (dx * sin(angle) + dy * cos(angle));
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction calcule les coordonnées 2D selon le mode de projection    */
/*   sélectionné (isométrique, vue de dessus, vue de côté).                   */
/*                                                                            */
/*   Modes de projection :                                                    */
/*   1. VIEW_ISO (Isométrique) :                                              */
/*      - x = (grid_x - grid_y) * cos(30°)                                    */
/*      - y = -z + (grid_x + grid_y) * sin(30°)                               */
/*                                                                            */
/*   2. VIEW_TOP (Vue de dessus) :                                            */
/*      - x = grid_x                                                          */
/*      - y = grid_y                                                          */
/*                                                                            */
/*   3. VIEW_SIDE (Vue latérale) :                                            */
/*      - x = grid_x                                                          */
/*      - y = -z                                                              */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers le mode de vue actuel                              */
/*   - grid_x, grid_y : coordonnées dans la grille                            */
/*   - z : hauteur du point                                                   */
/*                                                                            */
/*   Retourne:                                                                */
/*   - t_rot_point avec les coordonnées projetées                             */
/*                                                                            */
/* ************************************************************************** */
static t_rot_point	get_proj_coords(t_app *app, int grid_x, int grid_y, int z)
{
	t_rot_point	result;

	if (app->map.view_mode == VIEW_ISO)
	{
		result.x = (grid_x - grid_y) * cos(ISO_ANGLE);
		result.y = -z + (grid_x + grid_y) * sin(ISO_ANGLE);
	}
	else if (app->map.view_mode == VIEW_TOP)
	{
		result.x = grid_x;
		result.y = grid_y;
	}
	else if (app->map.view_mode == VIEW_SIDE)
	{
		result.x = grid_x;
		result.y = -z;
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction applique les transformations finales pour l'affichage     */
/*   du point dans la fenêtre.                                                */
/*                                                                            */
/*   Séquence de transformations :                                            */
/*   1. Échelle verticale (scale)                                             */
/*   2. Zoom uniforme (zoom)                                                  */
/*   3. Translation (shift_x, shift_y)                                        */
/*   4. Centrage dans la fenêtre (w_win/2, h_win/2)                           */
/*   5. Ajustement pour la taille de la grille                                */
/*   6. Décalage pour la barre latérale                                       */
/*                                                                            */
/*   Notes :                                                                  */
/*   - Les transformations sont appliquées dans un ordre spécifique           */
/*   - L'échelle et le zoom affectent proportionnellement x et y              */
/*   - Le centrage tient compte de la dimension totale de la grille           */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - point : pointeur vers le point à transformer                           */
/*   - app : pointeur vers les paramètres de transformation                   */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */

static void	apply_transformations(t_point *point, t_app *app)
{
	point->pos.x *= app->matrix.scale;
	point->pos.y *= app->matrix.scale;
	point->pos.x *= app->matrix.zoom;
	point->pos.y *= app->matrix.zoom;
	point->pos.x += app->matrix.shift_x;
	point->pos.y += app->matrix.shift_y;
	point->pos.x += app->sidebar.width \
		+ ((app->win.w_win - app->sidebar.width) / 2);
	point->pos.y += ((app->win.h_win / 2) / 2 / 2);
}
