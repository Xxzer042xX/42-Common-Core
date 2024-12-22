/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:01:34 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/19 14:14:39 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction déplace la carte dans la direction spécifiée en           */
/*   modifiant les coordonnées de translation (shift_x, shift_y).             */
/*                                                                            */
/*   Le déplacement s'effectue par pas de SHIFT_STEP (10) unités dans         */
/*   une des quatre directions possibles :                                    */
/*   - SHIFT_UP    : Déplacement vers le haut (-y)                            */
/*   - SHIFT_DOWN  : Déplacement vers le bas (+y)                             */
/*   - SHIFT_LEFT  : Déplacement vers la gauche (-x)                          */
/*   - SHIFT_RIGHT : Déplacement vers la droite (+x)                          */
/*                                                                            */
/*   Après le déplacement :                                                   */
/*   1. L'image est effacée (mise à zéro)                                     */
/*   2. Le flag needs_update est activé                                       */
/*   3. La carte est redessinée via render()                                  */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*   - direction : constante indiquant la direction du déplacement            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	shift_map(t_app *app, int direction)
{
	if (direction == SHIFT_UP)
		app->matrix.shift_y -= SHIFT_STEP;
	else if (direction == SHIFT_DOWN)
		app->matrix.shift_y += SHIFT_STEP;
	else if (direction == SHIFT_LEFT)
		app->matrix.shift_x -= SHIFT_STEP;
	else if (direction == SHIFT_RIGHT)
		app->matrix.shift_x += SHIFT_STEP;
	else
		return ;
	ft_memset(app->win.addr, 0, app->win.line_len * app->win.h_win);
	app->needs_update = 1;
	render(app);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction effectue une rotation de la carte autour de l'axe Z       */
/*   en modifiant l'angle de rotation (angle_z).                              */
/*                                                                            */
/*   La rotation s'effectue par pas de ROT_STEP (0.1) radians dans l'une      */
/*   des deux directions :                                                    */
/*   - ROT_LEFT  : Rotation anti-horaire (-angle)                             */
/*   - ROT_RIGHT : Rotation horaire (+angle)                                  */
/*                                                                            */
/*   L'angle est normalisé pour rester dans l'intervalle [0, 2π] :            */
/*   - Si angle_z ≥ 2π : soustrait 2π jusqu'à être dans l'intervalle          */
/*   - Si angle_z < 0  : ajoute 2π jusqu'à être dans l'intervalle             */
/*                                                                            */
/*   Après la rotation :                                                      */
/*   1. L'image est effacée (mise à zéro)                                     */
/*   2. Le flag needs_update est activé                                       */
/*   3. La carte est redessinée via render()                                  */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*   - direction : constante indiquant le sens de rotation                    */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	rotate_map(t_app *app, int direction)
{
	if (direction == ROT_LEFT)
		app->matrix.angle_z -= ROT_STEP;
	else if (direction == ROT_RIGHT)
		app->matrix.angle_z += ROT_STEP;
	while (app->matrix.angle_z >= 2 * M_PI)
		app->matrix.angle_z -= 2 * M_PI;
	while (app->matrix.angle_z < 0)
		app->matrix.angle_z += 2 * M_PI;
	ft_memset(app->win.addr, 0, app->win.line_len * app->win.h_win);
	app->needs_update = 1;
	render(app);
}
