/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:58:05 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/13 08:03:58 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	is_fdf_file(const char *filename);

/* ************************************************************************** */
/*                                                                            */
/*   Cette fonction est le point d'entrée principal du programme FdF.         */
/*   Elle vérifie d'abord le nombre d'arguments, initialise la structure      */
/*   Elle initialise l'application via init_app() et vérifie son succès.      */
/*   En cas d'échec, elle nettoie et termine avec le code d'erreur.           */
/*   Si l'initialisation réussit, elle entre dans une boucle de rendu qui     */
/*   continue tant que l'état est STATE_RUNNING. Dans cette boucle, elle      */
/*   configure le hook de rendu et lance la boucle principale de la MLX.      */
/*   À la fin, elle nettoie les ressources et retourne SUCCESS.               */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - ac : nombre d'arguments reçus                                          */
/*   - av : tableau des arguments, où av[1] est le fichier à traiter          */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS en cas de succès                                               */
/*   - Code d'erreur approprié en cas d'échec                                 */
/*                                                                            */
/* ************************************************************************** */
int	main(int ac, char **av)
{
	t_app	app;
	char	*filename;
	int		error;

	if (ac != 2 || is_fdf_file(av[1]) != SUCCESS)
		return (error_exit(ERR_ARGS));
	filename = av[1];
	ft_memset(&app, 0, sizeof(t_app));
	error = init_app(&app, filename);
	if (error != SUCCESS)
		return (cleanup_app(&app), error);
	mlx_loop_hook(app.win.mlx, render, &app);
	mlx_loop(app.win.mlx);
	return (cleanup_app(&app), SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*   Vérifie si le fichier spécifié a l'extension .fdf valide.                */
/*   La fonction effectue plusieurs vérifications :                           */
/*   - Vérifie si le nom du fichier n'est pas NULL                            */
/*   - Vérifie si le nom a une longueur minimale de 5 caractères              */
/*   - Vérifie la présence d'un point dans le nom du fichier                  */
/*   - Vérifie si l'extension après le point est exactement ".fdf"            */
/*                                                                            */
/*   Paramètre:                                                               */
/*   - filename : le nom du fichier à vérifier                                */
/*                                                                            */
/*   Retourne:                                                                */
/*   - SUCCESS si le fichier a une extension .fdf valide                      */
/*   - ERR_ARGS si l'une des vérifications échoue                             */
/*                                                                            */
/* ************************************************************************** */
static int	is_fdf_file(const char *filename)
{
	const char	*ext;

	if (!filename)
		return (ERR_ARGS);
	if (ft_strlen(filename) < 5)
		return (ERR_ARGS);
	ext = ft_strrchr(filename, '.');
	if (!ext)
		return (ERR_ARGS);
	if (ft_strncmp(ext, ".fdf", 4))
		return (ERR_ARGS);
	return (SUCCESS);
}
