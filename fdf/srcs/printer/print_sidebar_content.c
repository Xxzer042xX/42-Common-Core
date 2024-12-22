/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sidebar_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 01:57:25 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/17 01:57:25 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	print_sidebar_content(t_app *app)
{
	int		y_pos;

	y_pos = app->sidebar.y_offset;
	if (app->win.h_win != INIT_WIN_H && app->win.w_win != INIT_WIN_W)
		y_pos += app->win.h_win / 15;
	mlx_string_put(app->win.mlx, app->win.win, app->sidebar.x_pos + 35, y_pos,
		SILVER, app->sidebar.title);
	if (app->win.h_win != INIT_WIN_H && app->win.w_win != INIT_WIN_W)
		y_pos += app->win.h_win / 40;
	y_pos += app->sidebar.y_space_title;
	y_pos = print_controls(app, y_pos);
	y_pos += app->sidebar.y_space_title;
	if (app->win.h_win != INIT_WIN_H && app->win.w_win != INIT_WIN_W)
		y_pos += app->win.h_win / 8;
	mlx_string_put(app->win.mlx, app->win.win, app->sidebar.x_pos + 30, y_pos,
		SILVER, "Live Values:");
	if (app->win.h_win != INIT_WIN_H && app->win.w_win != INIT_WIN_W)
		y_pos += app->win.h_win / 40;
	y_pos += app->sidebar.y_space_title;
	print_live_values(app, y_pos);
}
