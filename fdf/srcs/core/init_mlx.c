/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:12:43 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/12 09:12:43 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction initialise l'environnement graphique MLX en plusieurs     */
/*   étapes successives :                                                     */
/*   1. Initialise la connexion MLX (mlx_init)                                */
/*   2. Récupère les dimensions de l'écran (mlx_get_screen_size)              */
/*   3. Définit les dimensions de la fenêtre selon INIT_WIN_W et INIT_WIN_H   */
/*   4. Crée une nouvelle fenêtre avec le titre défini dans TITLE             */
/*   5. Crée une nouvelle image MLX aux dimensions de la fenêtre              */
/*   6. Récupère l'adresse de l'image et ses propriétés :                     */
/*      - Bits par pixel (bbp)                                                */
/*      - Longueur de ligne (line_len)                                        */
/*      - Format d'endianness (endian)                                        */
/*                                                                            */
/*   La fonction vérifie chaque étape et retourne immédiatement en cas        */
/*   d'échec d'une des initialisations.                                       */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*          contenant la sous-structure win pour les éléments MLX             */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si toutes les initialisations MLX réussissent                  */
/*   - ERR_MLX si une des étapes suivantes échoue :                           */
/*     * Échec de mlx_init                                                    */
/*     * Échec de création de la fenêtre                                      */
/*     * Échec de création de l'image                                         */
/*     * Échec de récupération de l'adresse de l'image                        */
/*                                                                            */
/* ************************************************************************** */
int	init_mlx(t_app *app)
{
	app->win.mlx = mlx_init();
	if (!app->win.mlx)
		return (ERR_MLX);
	mlx_get_screen_size(app->win.mlx, &app->win.w_scr, &app->win.h_scr);
	app->win.w_win = INIT_WIN_W;
	app->win.h_win = INIT_WIN_H;
	app->win.win = mlx_new_window(app->win.mlx, \
									app->win.w_win, app->win.h_win, TITLE);
	if (!app->win.win)
		return (ERR_MLX);
	app->win.img = mlx_new_image(app->win.mlx, app->win.w_win, app->win.h_win);
	if (!app->win.img)
		return (ERR_MLX);
	app->win.addr = mlx_get_data_addr(app->win.img, &app->win.bbp, \
										&app->win.line_len, &app->win.endian);
	if (!app->win.addr)
		return (ERR_MLX);
	return (SUCCESS);
}
