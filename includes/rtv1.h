/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/02/26 11:24:59 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "ft_mlx.h"
# include "ft_tpool.h"

# define WIDTH			800
# define HEIGHT			600
# define TITLE			"RTV1 DX4000"
# define FILE_NAME		"saved_img/rt_XXX.bmp"

# define THREADS		8
# define TASKS			32

typedef struct	s_area {
	t_f128		x1;
	t_f128		y1;
	t_f128		x2;
	t_f128		y2;
	t_f128		zoom[2];
	t_u32		max;
	t_u32		size[2];
}				t_area;

typedef struct	s_env {
	t_tpool		*tp;
	int			keydown;
	int			refresh;
	int			show_fps;
	int			width;
	int			height;
	int			save_img;
}				t_env;

typedef struct	s_data {
	t_env		env;
	t_mlx		mlx;
}				t_data;

typedef struct	s_algo {
	t_data		*data;
	t_u32		start;
	t_u32		end;
}				t_algo;

int				env_init(t_env *env, int width, int height);
void			env_destroy(t_data *data);

void			check_key(t_env *env);
void			check_key2(t_env *env);
int				manage_key_down(int keycode, void *param);
int				manage_key_up(int keycode, void *param);
int				manage_mouse(int keycode, int x, int y, void *param);
int				manage_mouse_move(int x, int y, void *param);

void			draw_img(t_data *data);
void			clean_maps(t_data *data);
int				draw_rt(void *data);

int				write_header(int fd, int size[2]);
int				write_dibheader(int fd, int size[2]);
int				write_img(int fd, int size[2], t_color *map);
void			write_int(int fd, int n, int bytes);
int				save_img(t_data *data);

#endif
