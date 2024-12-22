/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:18:05 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/10 21:22:14 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	cleanup_map(t_app *app, int current_line);
static void	cleanup_windows(t_app *app);
static void	free_data_sidebar(t_app *app);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction principale de nettoyage libère toutes les ressources      */
/*   allouées par l'application dans l'ordre suivant :                        */
/*   1. Vérifie la validité du pointeur app                                   */
/*   2. Nettoie la carte (cleanup_map) en libérant tous les points            */
/*   3. Nettoie les ressources MLX (cleanup_windows)                          */
/*   4. Libère les données de la barre latérale (free_data_sidebar)           */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*          Si NULL, la fonction retourne sans action                         */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*   Note : Cette fonction est sécurisée contre les pointeurs NULL            */
/*                                                                            */
/* ************************************************************************** */
void	cleanup_app(t_app *app)
{
	if (!app)
		return ;
	cleanup_map(app, app->map.h_map);
	cleanup_windows(app);
	free_data_sidebar(app);
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction libère la mémoire allouée pour la carte en deux étapes :  */
/*   1. Libère chaque ligne de points individuellement, de 0 à current_line   */
/*      en vérifiant la validité de chaque pointeur                           */
/*   2. Libère le tableau principal de pointeurs et le met à NULL             */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*   - current_line : index maximum des lignes à nettoyer                     */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*   Note : Sécurisée contre les pointeurs NULL à tous les niveaux            */
/*                                                                            */
/* ************************************************************************** */
static void	cleanup_map(t_app *app, int current_line)
{
	int	i;

	if (!app || !app->map.points)
		return ;
	i = 0;
	while (i < current_line)
	{
		if (app->map.points[i])
			free (app->map.points[i]);
		i++;
	}
	free (app->map.points);
	app->map.points = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction nettoie les ressources graphiques MLX dans l'ordre :      */
/*   1. Détruit l'image MLX si elle existe                                    */
/*   2. Détruit la fenêtre si elle existe                                     */
/*   3. Détruit l'affichage MLX et libère son pointeur                        */
/*                                                                            */
/*   La fonction effectue les étapes dans cet ordre spécifique pour éviter    */
/*   les fuites mémoire. Après chaque libération, le pointeur correspondant   */
/*   est mis à NULL pour éviter toute utilisation ultérieure.                 */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*          Si NULL, la fonction retourne sans action                         */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	cleanup_windows(t_app *app)
{
	if (!app)
		return ;
	if (app->win.img)
		mlx_destroy_image(app->win.mlx, app->win.img);
	if (app->win.win)
		mlx_destroy_window(app->win.mlx, app->win.win);
	if (app->win.mlx)
	{
		mlx_destroy_display(app->win.mlx);
		free(app->win.mlx);
	}
	app->win.img = NULL;
	app->win.win = NULL;
	app->win.mlx = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction libère la mémoire allouée pour la barre latérale.         */
/*   Elle libère le tableau de paires de contrôles (ctrl_pairs) et met        */
/*   le pointeur à NULL pour éviter toute utilisation ultérieure.             */
/*                                                                            */
/*   Note : Les chaînes de caractères dans ctrl_pairs sont des constantes     */
/*   et ne doivent pas être libérées.                                         */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - app : pointeur vers la structure principale de l'application           */
/*                                                                            */
/*   Ne retourne rien (void)                                                  */
/*                                                                            */
/* ************************************************************************** */
static void	free_data_sidebar(t_app *app)
{
	if (app->sidebar.ctrl_pairs)
		free(app->sidebar.ctrl_pairs);
	app->sidebar.ctrl_pairs = NULL;
}
