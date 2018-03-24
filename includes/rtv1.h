/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/03/24 22:55:34 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "ft_type.h"
# include "ft_mlx.h"
# include "ft_tpool.h"
# include "matrix.h"
# include "objects.h"

# define FLOAT_INF		1e8
# define INTER_MIN		1e-8
# define BIAIS			1e-8
# define L_DIST_FACTOR	(-2.0 * 100.)
# define TITLE			"RTV1 DX4000"
# define FILE_NAME		"saved_img/rt_XXX.bmp"

# define THREADS		8
# define TASKS			32
# define MOVE_DELTA		2.0

typedef struct	s_ray {
	t_vec3		orig;
	t_vec3		dir;
}				t_ray;

typedef struct	s_solution {
	t_f64		t;
	t_f64		t0;
	t_f64		t1;
}				t_solution;

typedef struct	s_env {
	t_tpool		*tp;
	int			keydown;
	int			refresh;
	int			show_fps;
	int			save_img;
	int			width;
	int			height;
	t_color		background;
	t_f64		ratio;
	int			ratio_dir;
	t_obj_lst	*objects;
	t_vec3		cam_ang;
	t_vec3		cam_orig;
	t_f64		fov;
	t_matrix	rot;
	int			(*intersect[OBJECTS])(t_ray *, t_object *, t_solution *);
	void		(*norm[OBJECTS])(t_ray *, t_object *);
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

int				env_init(t_env *env, char *map);
void			env_destroy(t_data *data);

t_f64			clamp_f64(t_f64 f, t_f64 lmin, t_f64 lmax);
int				clamp_i32(int f, int lmin, int lmax);
int				ft_atof64_s(char *str, t_f64 *n);

void			check_key(t_env *env);
void			check_key2(t_env *env);
int				manage_key_down(int keycode, void *param);
int				manage_key_up(int keycode, void *param);
int				manage_mouse(int keycode, int x, int y, void *param);
int				manage_mouse_move(int x, int y, void *param);

void			clean_maps(t_data *data);
void			draw_img(t_data *data);
int				draw_rt(void *data);
void			pixel_to_screen(int x, int y, t_vec3 *camera, t_env *env);
void			compute_biais(t_ray *ray_hit, t_vec3 *p_hit_biais);
void			compute_hit(t_ray *ray, t_ray *ray_hit, t_f64 t);
t_color			convert_color(t_vec3 *color, t_vec3 *obj_color);
t_f64			compute_raylight(t_ray *ray, t_ray *ray_hit, t_ray *ray_light,
									t_object *obj);
t_f64			compute_reflect_ray(t_vec3 *v, t_vec3 *n, t_vec3 *l, t_f64 dln);
int				is_light(t_object *obj);
t_obj_lst		*find_next_light(t_obj_lst *lst);
t_obj_lst		*find_next_object(t_obj_lst *lst);
int				is_shadow(t_env *env, t_ray *ray_light, t_solution *solution);

void			color_intensity(t_vec3 *intensity, t_object *light, t_f64 dist);
void			color_ambient(t_vec3 *color, t_object *obj);
int				color_diffuse(t_vec3 *intensity, t_vec3 *color, t_object *obj,
								t_f64 *t);
void			color_specular(t_vec3 *intensity, t_vec3 *color, t_object *obj,
								t_f64 t);

void			norm_sphere(t_ray *ray_hit, t_object *obj);
void			norm_plane(t_ray *ray_hit, t_object *obj);
void			norm_cylinder(t_ray *ray_hit, t_object *obj);
void			norm_cone(t_ray *ray_hit, t_object *obj);
int				intersect_sphere(t_ray *ray, t_object *obj,
					t_solution *solution);
int				intersect_plane(t_ray *ray, t_object *obj,
					t_solution *solution);
int				intersect_cylinder(t_ray *ray, t_object *obj,
					t_solution *solution);
int				intersect_cone(t_ray *ray, t_object *obj,
					t_solution *solution);

int				write_header(int fd, int size[2]);
int				write_dibheader(int fd, int size[2]);
int				write_img(int fd, int size[2], t_color *map);
void			write_int(int fd, int n, int bytes);
int				save_img(t_data *data);

#endif
