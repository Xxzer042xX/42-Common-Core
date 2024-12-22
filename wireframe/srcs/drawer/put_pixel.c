/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelmeni <eljok87@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:59:31 by mdelmeni          #+#    #+#             */
/*   Updated: 2024/12/12 15:13:35 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static unsigned int	blender(unsigned int new, unsigned int old,	unsigned int a);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction place un pixel de couleur spécifique dans le buffer       */
/*   d'image MLX aux coordonnées données.                                     */
/*                                                                            */
/*   Processus de dessin :                                                    */
/*   1. Vérification des limites :                                            */
/*      - x dans [0, w_win[                                                   */
/*      - y dans [0, h_win[                                                   */
/*                                                                            */
/*   2. Calcul de l'adresse mémoire :                                         */
/*      position = addr + (y * line_len + x * (bbp/8))                        */
/*      - line_len : taille d'une ligne en octets                             */
/*      - bbp/8 : nombre d'octets par pixel                                   */
/*                                                                            */
/*   3. Écriture directe en mémoire :                                         */
/*      - Cast en unsigned int pour écrire la couleur                         */
/*      - Écriture uniquement si dans les limites                             */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale contenant :                */
/*          * win.addr : adresse du buffer d'image                            */
/*          * win.line_len : longueur d'une ligne en octets                   */
/*          * win.bbp : bits par pixel                                        */
/*          * win.w_win, win.h_win : dimensions de la fenêtre                 */
/*   - x, y : coordonnées du pixel                                            */
/*   - color : valeur de couleur au format RGB (0xRRGGBB)                     */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	put_pixel(t_app *app, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < app->win.w_win && y >= 0 && y < app->win.h_win)
	{
		dst = app->win.addr + (y * app->win.line_len + x * (app->win.bbp / 8));
		*(unsigned int *)dst = color;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction dessine un pixel avec support de transparence (RGBA).     */
/*   Elle mélange la nouvelle couleur avec la couleur existante selon         */
/*   la valeur alpha spécifiée.                                               */
/*                                                                            */
/*   Processus de dessin :                                                    */
/*   1. Vérification stricte des limites de la fenêtre                        */
/*                                                                            */
/*   2. Calcul de l'adresse du pixel dans le buffer :                         */
/*      position = addr + (y * line_len + x * (bbp/8))                        */
/*                                                                            */
/*   3. Gestion de la transparence :                                          */
/*      - Extraction de l'alpha (8 bits supérieurs)                           */
/*      - Si alpha = 255 : couleur opaque (application directe)               */
/*      - Sinon : mélange avec la couleur existante                           */
/*                                                                            */
/*   4. Mélange des composantes RGB :                                         */
/*      - Extraction séparée de R, G, B                                       */
/*      - Application de la formule de mélange pour chaque composante         */
/*      - Reconstruction de la couleur finale                                 */
/*                                                                            */
/*   Format de couleur : 0xAARRGGBB                                           */
/*   - AA : Canal alpha (transparence)                                        */
/*   - RR : Rouge                                                             */
/*   - GG : Vert                                                              */
/*   - BB : Bleu                                                              */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale                            */
/*   - x, y : coordonnées du pixel                                            */
/*   - color : valeur RGBA (0xAARRGGBB)                                       */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
void	put_pixel_rgba(t_app *app, int x, int y, int color)
{
	char			*dst;
	t_rgba			current;
	t_rgba			new;
	t_rgba			blend;

	if (x < 0 || x >= app->win.w_win || y < 0 || y >= app->win.h_win)
		return ;
	dst = app->win.addr + (y * app->win.line_len + x * (app->win.bbp / 8));
	current.hex = *(unsigned int *)dst;
	new.hex = color;
	if (new.a == 255)
	{
		*(unsigned int *)dst = color & 0x00FFFFFF;
		return ;
	}
	blend.b = blender(new.b, current.b, new.a);
	blend.g = blender(new.g, current.g, new.a);
	blend.r = blender(new.r, current.r, new.a);
	blend.a = 0;
	*(unsigned int *)dst = blend.hex;
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction calcule la valeur mélangée d'une composante de couleur    */
/*   en tenant compte de la transparence.                                     */
/*                                                                            */
/*   Formule de mélange :                                                     */
/*   (new_comp * alpha + old_comp * (255 - alpha)) / 255                      */
/*                                                                            */
/*   Processus de calcul :                                                    */
/*   1. Pondération de la nouvelle composante par alpha                       */
/*   2. Pondération de l'ancienne composante par (255 - alpha)                */
/*   3. Somme des deux valeurs                                                */
/*   4. Normalisation par division par 255                                    */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - new_comp : nouvelle composante de couleur (0-255)                      */
/*   - old_comp : composante de couleur existante (0-255)                     */
/*   - alpha : valeur de transparence (0-255)                                 */
/*            0 = transparent, 255 = opaque                                   */
/*                                                                            */
/*   Retourne:                                                                */
/*   - Composante de couleur mélangée (0-255)                                 */
/*                                                                            */
/* ************************************************************************** */
static unsigned int	blender(unsigned int new, unsigned int old, unsigned int a)
{
	int		new_color;

	new_color = (new * a + old * (255 - a)) / 255;
	return (new_color);
}
