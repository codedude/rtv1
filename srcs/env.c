/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 00:26:13 by vparis            #+#    #+#             */
/*   Updated: 2018/02/26 18:21:03 by vparis           ###   ########.fr       */
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

static void	env_init_scene(t_env *env)
{
	t_object	*objs[6];
	t_vec3		pos;
	t_vec3		color;
	t_vec3		e_color;

	vec3_set(&pos, 0.0, 20, -5);
	vec3_set(&color, 0.0, 0.0, 0.0);
	vec3_set(&e_color, 2, 2, 2);
	objs[0] = object_new(LIGHT, &pos, 3., &color, &e_color, 0, 0);

	vec3_set(&e_color, 0., 0., 0.);

	vec3_set(&pos, 0.0, -10004., -20.);
	vec3_set(&color, 0.70, 0.70, 0.70);
	objs[1] = object_new(SPHERE, &pos, 10000., &color, &e_color, 0, 0);

	vec3_set(&pos, 0.0, 0, -20);
	vec3_set(&color, 1.00, 0.32, 0.36);
	objs[2] = object_new(SPHERE, &pos, 4., &color, &e_color, 1, 0.5);

	vec3_set(&pos, 5.0, -1, -15);
	vec3_set(&color, 0.90, 0.76, 0.46);
	objs[3] = object_new(SPHERE, &pos, 2., &color, &e_color, 1, 0.0);

	vec3_set(&pos, 5.0, -1, -25);
	vec3_set(&color, 0.65, 0.77, 0.97);
	objs[4] = object_new(SPHERE, &pos, 3., &color, &e_color, 1, 0.0);

	vec3_set(&pos, -5.5, 0, -15);
	vec3_set(&color, 0.50, 0.90, 0.50);
	objs[5] = object_new(SPHERE, &pos, 3., &color, &e_color, 1, 0.0);

	object_add(&(env->objects), objs[0]);
	object_add(&(env->objects), objs[1]);
	object_add(&(env->objects), objs[2]);
	object_add(&(env->objects), objs[3]);
	object_add(&(env->objects), objs[4]);
	object_add(&(env->objects), objs[5]);
}

int		env_init(t_env *env, int width, int height)
{
	if ((env->tp = tp_create(THREADS, TP_ON_START)) == NULL)
		return (ERROR);
	env->keydown = -1;
	env->refresh = 1;
	env->show_fps = 0;
	env->save_img = 0;
	env_init_screen(env, width, height);
	env_init_scene(env);
	srand(time(NULL));
	return (SUCCESS);
}

void	env_destroy(t_data *data)
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
