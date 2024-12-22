/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:44:42 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/18 02:20:46 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/fdf.h"

static t_coord	init_delta(t_point start, t_point end);
static t_coord	init_direction(t_point start, t_point end);
static void		upd_pos(t_coord *cur, t_coord sign, int *error, t_coord delta);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction implémente l'algorithme de Bresenham pour dessiner une    */
/*   ligne entre deux points dans l'espace 2D.                                */
/*                                                                            */
/*   Processus de l'algorithme :                                              */
/*   1. Calcul des différences absolues (delta) entre points                  */
/*   2. Détermination des directions de progression (sign)                    */
/*   3. Initialisation de l'erreur (error = delta.x - delta.y)                */
/*   4. Tracé itératif :                                                      */
/*      - Dessine le pixel courant                                            */
/*      - Met à jour la position selon l'algorithme de Bresenham              */
/*      - Continue jusqu'à atteindre le point final                           */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - start : point de départ (coordonnées et couleur)                       */
/*   - end : point d'arrivée (coordonnées et couleur)                         */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	draw_line(t_app *app, t_point start, t_point end)
{
	t_coord	delta;
	t_coord	sign;
	t_coord	cur;
	int		error;

	delta = init_delta(start, end);
	sign = init_direction(start, end);
	error = delta.x - delta.y;
	cur = start.pos;
	while (cur.x != end.pos.x || cur.y != end.pos.y)
	{
		put_pixel(app, cur.x, cur.y, start.color.ref);
		upd_pos(&cur, sign, &error, delta);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction calcule les distances absolues entre les points de        */
/*   départ et d'arrivée pour l'algorithme de Bresenham.                      */
/*                                                                            */
/*   Calculs effectués :                                                      */
/*   - delta.x = |end.x - start.x| (distance horizontale)                     */
/*   - delta.y = |end.y - start.y| (distance verticale)                       */
/*                                                                            */
/*   Ces valeurs servent à :                                                  */
/*   - Déterminer la pente dominante de la ligne                              */
/*   - Calculer les erreurs d'approximation                                   */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - start : point de départ (t_point avec coordonnées)                     */
/*   - end : point d'arrivée (t_point avec coordonnées)                       */
/*                                                                            */
/*   Retourne:                                                                */
/*   - t_coord contenant les distances absolues en x et y                     */
/*                                                                            */
/* ************************************************************************** */
static t_coord	init_delta(t_point start, t_point end)
{
	t_coord	delta;

	delta.x = (int)fabs((double)(end.pos.x - start.pos.x));
	delta.y = (int)fabs((double)(end.pos.y - start.pos.y));
	return (delta);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction détermine le sens de progression pour chaque axe lors     */
/*   du tracé de la ligne.                                                    */
/*                                                                            */
/*   Logique de détermination :                                               */
/*   - Pour l'axe X :                                                         */
/*     * +1 si end.x > start.x (progression vers la droite)                   */
/*     * -1 si end.x < start.x (progression vers la gauche)                   */
/*   - Pour l'axe Y :                                                         */
/*     * +1 si end.y > start.y (progression vers le bas)                      */
/*     * -1 si end.y < start.y (progression vers le haut)                     */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - start : point de départ (t_point avec coordonnées)                     */
/*   - end : point d'arrivée (t_point avec coordonnées)                       */
/*                                                                            */
/*   Retourne:                                                                */
/*   - t_coord contenant les directions (-1 ou +1) pour x et y                */
/*                                                                            */
/* ************************************************************************** */
static t_coord	init_direction(t_point start, t_point end)
{
	t_coord	sign;

	if (start.pos.x < end.pos.x)
		sign.x = 1;
	else
		sign.x = -1;
	if (start.pos.y < end.pos.y)
		sign.y = 1;
	else
		sign.y = -1;
	return (sign);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction implémente le cœur de l'algorithme de Bresenham en        */
/*   mettant à jour la position courante lors du tracé.                       */
/*                                                                            */
/*   Algorithme :                                                             */
/*   1. Double l'erreur courante pour éviter les calculs fractionnaires       */
/*   2. Si error_doubled > -delta.y :                                         */
/*      - Déplace sur l'axe X dans la direction sign.x                        */
/*      - Ajuste l'erreur en soustrayant delta.y                              */
/*   3. Si error_doubled < delta.x :                                          */
/*      - Déplace sur l'axe Y dans la direction sign.y                        */
/*      - Ajuste l'erreur en ajoutant delta.x                                 */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - cur : pointeur vers la position courante à mettre à jour               */
/*   - sign : directions de progression (-1 ou +1) pour chaque axe            */
/*   - error : pointeur vers la variable d'erreur de Bresenham                */
/*   - delta : distances absolues entre les points                            */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	upd_pos(t_coord *cur, t_coord sign, int *error, t_coord delta)
{
	int	error_doubled;

	error_doubled = *error * 2;
	if (error_doubled > -delta.y)
	{
		*error -= delta.y;
		cur->x += sign.x;
	}
	if (error_doubled < delta.x)
	{
		*error += delta.x;
		cur->y += sign.y;
	}
}
