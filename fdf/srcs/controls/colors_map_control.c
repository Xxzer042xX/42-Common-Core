/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:49:42 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/16 01:49:42 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	define_colors(t_app *app);
static int	define_colors_aux(t_app *app);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction gère le changement cyclique des couleurs de la grille.    */
/*                                                                            */
/*   Processus de changement :                                                */
/*   1. Incrémentation cyclique du mode couleur (0-15)                        */
/*                                                                            */
/*   2. Parcours de tous les points de la carte :                             */
/*      - Ne modifie que les points sans couleur parsée                       */
/*      - Applique la nouvelle couleur via define_colors                      */
/*                                                                            */
/*   3. Mise à jour de l'affichage :                                          */
/*      - Efface le contenu actuel du buffer                                  */
/*      - Active le flag de mise à jour                                       */
/*      - Déclenche un nouveau rendu                                          */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale contenant :                */
/*          * La carte et ses dimensions                                      */
/*          * Le mode de couleur actuel                                       */
/*          * Les paramètres d'affichage                                      */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	change_grid_color(t_app *app)
{
	int		i;
	int		j;
	int		color;

	app->map.color_mode = (app->map.color_mode + 1) % 16;
	i = 0;
	while (i < app->map.h_map)
	{
		j = 0;
		while (j < app->map.w_map)
		{
			if (app->map.points[i][j].color.is_parsed == 0)
			{
				color = define_colors(app);
				app->map.points[i][j].color.ref = color;
			}
			j++;
		}
		i++;
	}
	ft_memset(app->win.addr, 0, app->win.line_len * app->win.h_win);
	app->needs_update = 1;
	render(app);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction détermine la couleur à utiliser selon le mode actuel      */
/*   (modes 0-8).                                                             */
/*                                                                            */
/*   Table des couleurs :                                                     */
/*   0 - PURPLE   : Violet                                                    */
/*   1 - GREEN    : Vert                                                      */
/*   2 - BLUE     : Bleu                                                      */
/*   3 - RED      : Rouge                                                     */
/*   4 - CYAN     : Cyan                                                      */
/*   5 - ORANGE   : Orange                                                    */
/*   6 - BROWN    : Marron                                                    */
/*   7 - GREY     : Gris                                                      */
/*   8 - WHITE    : Blanc                                                     */
/*   9+ - Appel à define_colors_aux pour les modes supérieurs                 */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure contenant le mode couleur             */
/*                                                                            */
/*   Retourne:                                                                */
/*   - Valeur de couleur RGB correspondant au mode                            */
/*                                                                            */
/* ************************************************************************** */
static int	define_colors(t_app *app)
{
	int		color;

	color = 0;
	if (app->map.color_mode == 0)
		color = PURPLE;
	else if (app->map.color_mode == 1)
		color = GREEN;
	else if (app->map.color_mode == 2)
		color = BLUE;
	else if (app->map.color_mode == 3)
		color = RED;
	else if (app->map.color_mode == 4)
		color = CYAN;
	else if (app->map.color_mode == 5)
		color = ORANGE;
	else if (app->map.color_mode == 6)
		color = BROWN;
	else if (app->map.color_mode == 7)
		color = GREY;
	else if (app->map.color_mode == 8)
		color = WHITE;
	else
		color = define_colors_aux(app);
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction auxiliaire détermine la couleur pour les modes 9-15.      */
/*                                                                            */
/*   Table des couleurs étendues :                                            */
/*   9  - SILVER   : Argent                                                   */
/*   10 - GOLD     : Or                                                       */
/*   11 - BRONZE   : Bronze                                                   */
/*   12 - PLATINUM : Platine                                                  */
/*   13 - COPPER   : Cuivre                                                   */
/*   14 - BRASS    : Laiton                                                   */
/*   15 - YELLOW   : Jaune                                                    */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure contenant le mode couleur             */
/*                                                                            */
/*   Retourne:                                                                */
/*   - Valeur de couleur RGB correspondant au mode                            */
/*   - 0 si mode non reconnu                                                  */
/*                                                                            */
/* ************************************************************************** */
static int	define_colors_aux(t_app *app)
{
	int	color;

	color = 0;
	if (app->map.color_mode == 9)
		color = SILVER;
	else if (app->map.color_mode == 10)
		color = GOLD;
	else if (app->map.color_mode == 11)
		color = BRONZE;
	else if (app->map.color_mode == 12)
		color = PLATINUM;
	else if (app->map.color_mode == 13)
		color = COPPER;
	else if (app->map.color_mode == 14)
		color = BRASS;
	else if (app->map.color_mode == 15)
		color = YELLOW;
	return (color);
}
