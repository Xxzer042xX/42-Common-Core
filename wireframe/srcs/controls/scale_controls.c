/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:35:56 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/15 02:06:49 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction modifie l'échelle verticale (hauteur) de la carte en      */
/*   ajustant le facteur d'échelle (matrix.scale).                            */
/*                                                                            */
/*   Le changement d'échelle s'effectue par pas de SCALE_STEP dans l'une      */
/*   des deux directions :                                                    */
/*   - SCALE_INCREASE : Augmente la hauteur (+SCALE_STEP)                     */
/*   - SCALE_DECREASE : Diminue la hauteur (-SCALE_STEP)                      */
/*                                                                            */
/*   Contraintes de sécurité :                                                */
/*   - Une limite minimale de 0.1f est imposée pour éviter l'aplatissement    */
/*     complet de la carte                                                    */
/*                                                                            */
/*   Après le changement d'échelle :                                          */
/*   1. L'image est effacée (mise à zéro)                                     */
/*   2. Le flag needs_update est activé                                       */
/*   3. La carte est redessinée via render()                                  */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*          contenant la matrice de transformation                            */
/*   - direction : constante indiquant le sens du changement d'échelle        */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	scale_map(t_app *app, int direction)
{
	if (direction == SCALE_INCREASE)
		app->matrix.scale += SCALE_STEP;
	else if (direction == SCALE_DECREASE)
		app->matrix.scale -= SCALE_STEP;
	if (app->matrix.scale < 0.1f)
		app->matrix.scale = 0.1f;
	ft_memset(app->win.addr, 0, app->win.line_len * app->win.h_win);
	app->needs_update = 1;
	render(app);
}
