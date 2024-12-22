/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler_mouse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:59:03 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/13 21:09:43 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction gère les événements de la molette de souris pour          */
/*   contrôler le zoom de la vue.                                             */
/*                                                                            */
/*   Événements traités :                                                     */
/*   1. SCROLL_UP (molette vers le haut) :                                    */
/*      - Zoom avant                                                          */
/*      - Applique le facteur Z_IN à la vue                                   */
/*                                                                            */
/*   2. SCROLL_DOWN (molette vers le bas) :                                   */
/*      - Zoom arrière                                                        */
/*      - Applique le facteur Z_OUT à la vue                                  */
/*                                                                            */
/*   Note : Les coordonnées x,y du curseur sont enregistrées mais             */
/*   actuellement non utilisées pour le zoom. Elles pourraient servir         */
/*   à implémenter un zoom centré sur la position du curseur.                 */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - keycode : identifiant de l'événement souris (SCROLL_UP/DOWN)           */
/*   - x : position horizontale du curseur en pixels                          */
/*   - y : position verticale du curseur en pixels                            */
/*   - param : pointeur void vers t_app, casté en interne                     */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS dans tous les cas                                              */
/*   Le retour est utilisé par le hook MLX mais n'affecte pas                 */
/*   le comportement du programme                                             */
/*                                                                            */
/* ************************************************************************** */
int	handle_mouse(int keycode, int x, int y, void *param)
{
	t_app	*app;

	(void)x;
	(void)y;
	app = (t_app *)param;
	if (keycode == SCROLL_UP)
		zoom(app, Z_IN);
	if (keycode == SCROLL_DOWN)
		zoom(app, Z_OUT);
	return (SUCCESS);
}
