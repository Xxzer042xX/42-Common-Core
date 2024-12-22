/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_sidebar_control.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:13:51 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/15 22:13:51 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	define_color_opacity(t_app *app);
static int	define_color_opacity_aux(t_app *app);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction principale gère le changement cyclique des couleurs de    */
/*   la barre latérale avec une transparence fixe de 50%.                     */
/*                                                                            */
/*   Processus de changement :                                                */
/*   1. Incrémentation cyclique du mode couleur (0-15)                        */
/*   2. Récupération de la nouvelle couleur avec transparence                 */
/*   3. Application à la barre latérale via l'union rgba                      */
/*   4. Effacement du buffer d'affichage                                      */
/*   5. Déclenchement d'un nouveau rendu                                      */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	change_sidebar_color(t_app *app)
{
	int		color;

	app->sidebar.color_mode = (app->sidebar.color_mode + 1) % 16;
	color = define_color_opacity(app);
	app->sidebar.color.hex = color;
	ft_memset(app->win.addr, 0, app->win.line_len * app->win.h_win);
	app->needs_update = 1;
	render(app);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction détermine la couleur semi-transparente pour les modes     */
/*   0 à 8 de la barre latérale.                                              */
/*                                                                            */
/*   Table des couleurs avec 50% d'opacité :                                  */
/*   0 - PURPLE_50  : Violet                                                  */
/*   1 - GREEN_50   : Vert                                                    */
/*   2 - BLUE_50    : Bleu                                                    */
/*   3 - RED_50     : Rouge                                                   */
/*   4 - CYAN_50    : Cyan                                                    */
/*   5 - ORANGE_50  : Orange                                                  */
/*   6 - BROWN_50   : Marron                                                  */
/*   7 - GREY_50    : Gris                                                    */
/*   8 - WHITE_50   : Blanc                                                   */
/*   9+ - Appel à define_color_opacity_aux                                    */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*                                                                            */
/*   Retourne:                                                                */
/*   - Valeur de couleur RGBA avec transparence à 50%                         */
/*                                                                            */
/* ************************************************************************** */
static int	define_color_opacity(t_app *app)
{
	int		color;

	color = 0;
	if (app->sidebar.color_mode == 0)
		color = PURPLE_50;
	else if (app->sidebar.color_mode == 1)
		color = GREEN_50;
	else if (app->sidebar.color_mode == 2)
		color = BLUE_50;
	else if (app->sidebar.color_mode == 3)
		color = RED_50;
	else if (app->sidebar.color_mode == 4)
		color = CYAN_50;
	else if (app->sidebar.color_mode == 5)
		color = ORANGE_50;
	else if (app->sidebar.color_mode == 6)
		color = BROWN_50;
	else if (app->sidebar.color_mode == 7)
		color = GREY_50;
	else if (app->sidebar.color_mode == 8)
		color = WHITE_50;
	else
		color = define_color_opacity_aux(app);
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction auxiliaire détermine la couleur semi-transparente pour    */
/*   les modes 9 à 15 de la barre latérale.                                   */
/*                                                                            */
/*   Table des couleurs étendues avec 50% d'opacité :                         */
/*   9  - SILVER_50   : Argent                                                */
/*   10 - GOLD_50     : Or                                                    */
/*   11 - BRONZE_50   : Bronze                                                */
/*   12 - PLATINUM_50 : Platine                                               */
/*   13 - COPPER_50   : Cuivre                                                */
/*   14 - BRASS_50    : Laiton                                                */
/*   15 - YELLOW_50   : Jaune                                                 */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*                                                                            */
/*   Retourne:                                                                */
/*   - Valeur de couleur RGBA avec transparence à 50%                         */
/*   - 0 si mode non reconnu                                                  */
/*                                                                            */
/* ************************************************************************** */
static int	define_color_opacity_aux(t_app *app)
{
	int	color;

	color = 0;
	if (app->sidebar.color_mode == 9)
		color = SILVER_50;
	else if (app->sidebar.color_mode == 10)
		color = GOLD_50;
	else if (app->sidebar.color_mode == 11)
		color = BRONZE_50;
	else if (app->sidebar.color_mode == 12)
		color = PLATINUM_50;
	else if (app->sidebar.color_mode == 13)
		color = COPPER_50;
	else if (app->sidebar.color_mode == 14)
		color = BRASS_50;
	else if (app->sidebar.color_mode == 15)
		color = YELLOW_50;
	return (color);
}
