/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/03/08 21:40:44 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "ft_mlx.h"
# include "ft_tpool.h"
# include "matrix.h"
# include "objects.h"

# define WIDTH			1024
# define HEIGHT			768
# define FOV			72.
# define MAX_DEPTH		8
# define FLOAT_INF		1e9
# define INTER_MIN		1e-10
# define BIAIS			1e-8
# define TITLE			"RTV1 DX4000"
# define FILE_NAME		"saved_img/rt_XXX.bmp"

# define THREADS		8
# define TASKS			32
# define MOVE_DELTA		2.0

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
	int			save_img;
	int			width;
	int			height;
	t_f64		ratio;
	int			ratio_dir;
	t_obj_lst	*objects;
	t_vec3		cam_ang;
	t_vec3		cam_orig;
	t_matrix	rot;
}				t_env;

typedef struct	s_data {
	t_env		env;
	t_mlx		mlx;
}				t_data;

typedef struct	s_algo {
	t_data		*data;
	int			start;
	int			end;
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
t_color			convert_color(t_vec3 *color);
void			pixel_to_screen(int x, int y, t_vec3 *camera, t_env *env);
int				intersect_sphere(t_vec3 *orig, t_vec3 *dir, t_object *obj,
									t_f64 *t0, t_f64 *t1);
int				intersect_plane(t_vec3 *orig, t_vec3 *dir, t_object *obj,
								t_f64 *t);
int				intersect_cylinder(t_vec3 *orig, t_vec3 *dir, t_object *obj,
								t_f64 *t0, t_f64 *t1);
int				intersect_cone(t_vec3 *orig, t_vec3 *dir, t_object *obj,
								t_f64 *t0, t_f64 *t1);

int				write_header(int fd, int size[2]);
int				write_dibheader(int fd, int size[2]);
int				write_img(int fd, int size[2], t_color *map);
void			write_int(int fd, int n, int bytes);
int				save_img(t_data *data);

#endif
