/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:22:50 by vparis            #+#    #+#             */
/*   Updated: 2018/02/26 18:38:17 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "matrix.h"
#include "objects.h"
#include "rtv1.h"

/*
** Convert pixel(int x, int y) to NDC
** Convert NDC(float x, float y) to SCREEN with aspect ratio and FOV [-1:1]
*/

static void		pixel_to_screen(int x, int y, t_vec3 *camera, t_env *env)
{
	t_f64	fov;

	fov = ft_tan(FOV / 2.);
	camera->x = ((t_f64)x + 0.5) / (t_f64)env->width;
	camera->y = ((t_f64)y + 0.5) / (t_f64)env->height;
	if (env->ratio_dir == 1)
	{
		camera->x = ((2 * camera->x - 1.) * env->ratio) * fov;
		camera->y = (1. - 2 * camera->y) * fov;
	}
	else if (env->ratio_dir == -1)
	{
		camera->x = (2 * camera->x - 1.) * fov;
		camera->y = ((1. - 2 * camera->y) * env->ratio) * fov;
	}
	else
	{
		camera->x = (2 * camera->x - 1.) * fov;
		camera->y = (1. - 2 * camera->y) * fov;
	}
	camera->z = -1.;
}

/*
** HIT = SUCCESS
*/

static int		intersect_sphere(t_vec3 *orig, t_vec3 *dir, t_object *obj, 
									t_f64 *t0, t_f64 *t1)
{
	t_f64		tca;
	t_f64		d2;
	t_f64		thc;
	t_vec3		l;

	vec3_set(&l, obj->pos.x, obj->pos.y, obj->pos.z);
	vec3_sub(&l, orig);
	tca = vec3_dot(&l, dir);
	if (tca < 0.)
		return (ERROR);
	d2 = vec3_dot(&l, &l) - tca * tca;
	if (d2 > obj->radius2) 
		return (ERROR);
	thc = sqrt(obj->radius2 - d2);
	*t0 = tca - thc;
	*t1 = tca + thc; 
	return (SUCCESS);
}

static t_object	*trace(t_vec3 *orig, t_vec3 *dir, t_obj_lst *objects, t_f64 *t)
{
	t_obj_lst	*iter;
	t_object	*obj;
	t_f64		t0;
	t_f64		t1;

	iter = objects;
	*t = 1e8;
	obj = NULL;
	while (iter != NULL)
	{
		if (intersect_sphere(orig, dir, iter->object, &t0, &t1) == SUCCESS)
		{
			if (t0 < 0.)
				t0 = t1;
			if (t0 < *t)
			{
				*t = t0;
				obj = iter->object;
			}
		}
		iter = iter->next;
	}
	return (obj);
}

static t_color	convert_color(t_vec3 *color)
{
	int	x;
	int	y;
	int	z;

	x = color->x < 1. ? color->x : 1.;
	y = color->y < 1. ? color->y : 1.;
	z = color->z < 1. ? color->z : 1.;
	x = (unsigned char)(x * 255.);
	y = (unsigned char)(y * 255.);
	z = (unsigned char)(z * 255.);
	return (ft_mlx_getcolor((int)x, (int)y, (int)z));
}

static t_f64	mix(t_f64 a, t_f64 b, t_f64 mix)
{
	return (b * mix + a * (1 - mix));
} 

static t_color	compute_color(t_vec3 *orig, t_vec3 *dir, t_object *obj, 
							t_obj_lst *objects, t_f64 t, int depth)
{
	t_obj_lst	*iter_light;
	t_obj_lst	*iter;
	t_vec3		color;
	t_vec3		tmp;
	t_vec3		p_hit;
	t_vec3		n_hit;
	t_vec3		inter;
	t_vec3		light;
	t_f64		biais;
	t_f64		t0;
	t_f64		t1;
	int			inside;
	int			shadow;

	biais = 1e-4;
	inside = 0;
	vec3_set(&color, 0., 0., 0.);
	vec3_set(&tmp, dir->x, dir->y, dir->z);
	vec3_mul(&tmp, t);
	vec3_set(&p_hit, orig->x, orig->y, orig->z);
	vec3_add(&p_hit, &tmp);
	vec3_set(&n_hit, p_hit.x, p_hit.y, p_hit.z);
	vec3_sub(&n_hit, &(obj->pos));
	vec3_norm(&n_hit);
	if (vec3_dot(dir, &n_hit) > 0.)
	{
		vec3_mul(&n_hit, -1.);
		inside = 1;
	}
	vec3_cpy(&inter, &n_hit);
	vec3_mul(&inter, biais);
	vec3_add(&inter, &p_hit);

	if ((obj->transparency > 0. || obj->reflection > 0.) && depth < MAX_DEPTH
		&& 0)
	{

	}
	else
	{
		iter_light = objects;
		while (iter_light != NULL)
		{
			if (iter_light->object->type == LIGHT)
			{
				shadow = 0;
				vec3_set(&light, iter_light->object->pos.x, 
					iter_light->object->pos.y, iter_light->object->pos.z);
				vec3_sub(&light, &p_hit);
				vec3_norm(&light);
				iter = objects;
				while (iter != NULL)
				{
					if (iter_light != iter)
					{
						if (intersect_sphere(&inter, &light, iter->object, 
							&t0, &t1) == SUCCESS)
						{
							shadow = 1;
							break ;
						}
					}
					iter = iter->next;
				}
				if (shadow == 0)
				{
					vec3_set(&tmp, obj->color.x, obj->color.y, obj->color.z);
					vec3_mul3(&tmp, &(iter_light->object->e_color));
					t0 = vec3_dot(&n_hit, &light);
					vec3_mul(&tmp, (t0 > 0.) ? t0 : 0.);
					vec3_add(&color, &tmp);
				}
			}
			iter_light = iter_light->next;
		}
	}
	vec3_add(&color, &(obj->e_color));
	return (convert_color(&color));
}


/*
**	CameraSpace = Convert pixel to screen (ration, fov [-1:1])
**	Ray origin : (0, 0, 0)
**	Ray dir = CameraSpace - Ray origin
**	Ray dir = normalize
**	Trace ray
*/

int				draw_rt(void *data)
{
	t_algo		*algo;
	t_object	*obj;
	t_color		color;
	t_vec3		orig;
	t_vec3		dir;
	t_vec3		camera;
	t_f64		t;
	int			i;
	int			j;
	t_matrix	rot;

	algo = (t_algo *)data;
	i = algo->start;
	rot = matrix_rot(&(algo->data->env.ang));
	while (i < algo->end)
	{
		j = 0;
		while (j < algo->data->env.width)
		{
			pixel_to_screen(j, i, &camera, &(algo->data->env));
			vec3_set(&orig, 0., 0., 0.);
			vec3_set(&dir, camera.x, camera.y, camera.z);
			matrix_mul3_vec3(rot, &dir);
			vec3_norm(&dir);
			obj = trace(&orig, &dir, algo->data->env.objects, &t);
			if (obj != NULL)
			{
				if (obj->type != LIGHT)
				{
					color = compute_color(&orig, &dir, obj,
						algo->data->env.objects, t, 0);
					ft_mlx_put(&(algo->data->mlx), j, i, color);
				}
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}