/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:32:26 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/15 02:01:56 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCTS_H
# define FT_STRUCTS_H

/* ************************************************************************** */
/*                         ROTATION, SCALE AND SHIFT MAP ENUMS                */
/* ************************************************************************** */
enum e_shift_dir
{
	SHIFT_UP,
	SHIFT_DOWN,
	SHIFT_LEFT,
	SHIFT_RIGHT
};

enum e_rot_dir
{
	ROT_LEFT,
	ROT_RIGHT
};

enum e_scale
{
	SCALE_INCREASE,
	SCALE_DECREASE
};

/* ************************************************************************** */
/*                                VIEWS ENUMS                                 */
/* ************************************************************************** */
enum e_view_mode
{
	VIEW_ISO,
	VIEW_TOP,
	VIEW_SIDE
};

/* ************************************************************************** */
/*                                ERROR AND STATE ENUMS                       */
/* ************************************************************************** */
enum e_error
{
	SUCCESS,
	ERR_ARGS,
	ERR_MALLOC,
	ERR_DATA,
	ERR_FILE,
	ERR_FORMAT,
	ERR_MLX,
	DEBUG
};

enum e_app_state
{
	STATE_KILL,
	STATE_INIT,
	STATE_RUNNING
};

/* ************************************************************************** */
/*                              SIDEBAR STRUCTURE AND UNION                   */
/* ************************************************************************** */
typedef struct s_control_pair
{
	char	*key;
	char	*value;
}	t_control_pair;

typedef union u_rgba
{
	int	hex;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	};
}	t_rgba;

typedef struct s_sidebar
{
	t_control_pair	*ctrl_pairs;
	t_rgba			color;
	char			*title;
	int				x_pos;
	int				x_offset;
	int				y_offset;
	int				y_pos;
	int				y_space_title;
	int				y_space_ctrl;
	int				ctrl_count;
	int				width;
	int				height;
	int				color_mode;
}	t_sidebar;

/* ************************************************************************** */
/*                                POINT STRUCTURE                             */
/* ************************************************************************** */
typedef union u_coord
{
	int	coords[3];
	struct
	{
		int	x;
		int	y;
		int	z;
	};
}	t_coord;

typedef struct s_color
{
	int	ref;
	int	is_parsed;
}	t_color;

typedef struct s_rot_point
{
	double	x;
	double	y;
}	t_rot_point;

typedef struct s_point
{
	t_rot_point	rot;
	t_coord		original_pos;
	t_coord		pos;
	t_color		color;
	float		elevation;
}	t_point;

/* ************************************************************************** */
/*                                WINDOWS STRUCTURE                           */
/* ************************************************************************** */

typedef struct s_win
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		w_scr;
	int		h_scr;
	int		w_win;
	int		h_win;
	int		bbp;
	int		line_len;
	int		endian;
	int		mouse_x;
	int		mouse_y;
	int		mouse_pressed;
}	t_win;

/* ************************************************************************** */
/*                                MAP STRUCTURE                               */
/* ************************************************************************** */

typedef struct s_map
{
	t_point				**points;
	enum e_view_mode	view_mode;
	float				z_min;
	float				z_max;
	float				z_range;
	float				z_scale;
	float				center_x;
	float				center_y;
	int					color_mode;
	int					w_map;
	int					h_map;
}	t_map;

/* ************************************************************************** */
/*                              TRANSFORM STRUCTURE                           */
/* ************************************************************************** */

typedef struct s_matrix
{
	float	angle_x;
	float	angle_y;
	float	angle_z;
	float	scale;
	float	shift_x;
	float	shift_y;
	float	zoom;
	float	space;
	float	iso_angle;
	float	center_x;
	float	center_y;
	float	altitude_factor;
	int		auto_rot;
}	t_matrix;

/* ************************************************************************** */
/*                              MAIN APP STRUCTURE                            */
/* ************************************************************************** */

typedef struct s_app
{
	t_map				map;
	t_win				win;
	t_matrix			matrix;
	t_sidebar			sidebar;
	enum e_app_state	state;
	enum e_shift_dir	shift_dir;
	enum e_rot_dir		rot_dir;
	enum e_scale		scale;
	int					needs_update;
}	t_app;

#endif
