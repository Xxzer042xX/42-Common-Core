/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer_sidebar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:48:18 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/13 00:28:27 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction dessine le fond rectangulaire de la barre latérale        */
/*   qui contiendra les contrôles et informations de l'interface.             */
/*                                                                            */
/*   Processus de dessin :                                                    */
/*   1. Définit la zone de dessin basée sur sidebar :                         */
/*      - Largeur : de 0 à sidebar.width                                      */
/*      - Hauteur : de 0 à sidebar.height                                     */
/*                                                                            */
/*   2. Remplit la zone pixel par pixel :                                     */
/*      - Parcourt chaque ligne (y)                                           */
/*      - Pour chaque ligne, parcourt chaque colonne (x)                      */
/*      - Utilise put_pixel pour dessiner avec COLOR_MENU                     */
/*                                                                            */
/*   Vérifications :                                                          */
/*   - Assure que chaque pixel est dans les limites de la sidebar             */
/*   - Évite tout débordement hors de la zone définie                         */
/*                                                                            */
/*   Note : Cette fonction crée le fond sur lequel seront ensuite             */
/*   affichés les textes et contrôles de l'interface.                         */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale contenant :                */
/*          * sidebar.width : largeur de la barre latérale                    */
/*          * sidebar.height : hauteur de la barre latérale                   */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	draw_sidebar(t_app *app)
{
	int		x;
	int		y;
	int		h_win;
	int		w_win;

	x = 0;
	y = 0;
	h_win = app->sidebar.height;
	w_win = app->sidebar.width;
	while (y < h_win)
	{
		x = 0;
		while (x < w_win)
		{
			if (y < h_win && x < w_win)
				put_pixel_rgba(app, x, y, app->sidebar.color.hex);
			x++;
		}
		y++;
	}
}
