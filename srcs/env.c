/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 00:26:13 by vparis            #+#    #+#             */
/*   Updated: 2018/03/15 11:05:04 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "libft.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "rtv1.h"
#include "matrix.h"
#include "objects.h"
#include "ft_tpool.h"
#include "parser.h"

static void	env_init_screen(t_env *env, int width, int height)
{
	env->width = width;
	env->height = height;
	if (width > height)
	{
		env->ratio = (t_f64)width / (t_f64)height;
		env->ratio_dir = 1;
	}
	else if (width < height)
	{
		env->ratio = (t_f64)height / (t_f64)width;
		env->ratio_dir = -1;
	}
	else
	{
		env->ratio = 1.;
		env->ratio_dir = 0;
	}
}

static void	env_init_shapes(t_env *env)
{
	env->intersect[PLANE] = &intersect_plane;
	env->intersect[SPHERE] = &intersect_sphere;
	env->intersect[CONE] = &intersect_cone;
	env->intersect[CYLINDER] = &intersect_cylinder;
	env->norm[PLANE] = &norm_plane;
	env->norm[SPHERE] = &norm_sphere;
	env->norm[CONE] = &norm_cone;
	env->norm[CYLINDER] = &norm_cylinder;
}

int			env_init(t_env *env, char *map, int width, int height)
{
	if ((env->tp = tp_create(THREADS, TP_ON_START)) == NULL)
		return (ERROR);
	env->keydown = -1;
	env->refresh = 1;
	env->show_fps = 0;
	env->save_img = 0;
	vec3_set(&(env->cam_orig), 0.0, 16.0, 60.);
	vec3_set(&(env->cam_ang), -12.0, 0.0, 0.0);
	env_init_screen(env, width, height);
	env_init_scene(env);
	env_init_shapes(env);
	srand(time(NULL));
	return (parse_map(env, map));
}

void		env_destroy(t_data *data)
{
	int	i;

	tp_destroy(&(data->env.tp));
	i = 0;
	while (i < MLX_MAX_WINDOW)
	{
		ft_mlx_destroy(&(data->mlx), i);
		i++;
	}
	object_free(&(data->env.objects));
	ft_mlx_exit();
}
