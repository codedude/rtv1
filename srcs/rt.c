/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:22:50 by vparis            #+#    #+#             */
/*   Updated: 2018/03/06 18:59:39 by vparis           ###   ########.fr       */
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

void			mix_color(t_vec3 *color, t_vec3 *obj_color, t_vec3 *light_color, 						t_f64 t)
{
	t_vec3	tmp;

	if (t > 0.)
	{
		vec3_cpy(&tmp, obj_color);
		vec3_mul(&tmp, light_color);
		vec3_mul_scalar(&tmp, t);
		vec3_add(color, &tmp);
	}
}
void			compute_biais(t_vec3 *n_hit, t_vec3 *p_hit, t_vec3 *p_hit_biais)
{
	vec3_cpy(p_hit_biais, n_hit);
	vec3_mul_scalar(p_hit_biais, BIAIS);
	vec3_add(p_hit_biais, p_hit);
}

void			compute_hit(t_vec3 *orig, t_vec3 *dir, t_object *obj, 
							t_vec3 *n_hit, t_vec3 *p_hit, t_f64 t)
{
	t_vec3	tmp;

	vec3_cpy(&tmp, dir);
	vec3_mul_scalar(&tmp, t);
	vec3_cpy(p_hit, orig);
	vec3_add(p_hit, &tmp);
	if (obj->type == SPHERE)
	{
		vec3_cpy(n_hit, p_hit);
		vec3_sub(n_hit, &(obj->pos));
		vec3_norm(n_hit);
	}
	else if (obj->type == PLANE)
		vec3_cpy(n_hit, &(obj->norm));
	else if (obj->type == CYLIND)
	{
		vec3_cpy(n_hit, p_hit);
		vec3_sub(n_hit, &(obj->pos));
		vec3_norm(n_hit);
	}
	
}

static t_color	compute_color(t_vec3 *orig, t_vec3 *dir, t_object *obj, 
							t_obj_lst *objects, t_f64 t)
{
	t_obj_lst	*iter_light;
	t_obj_lst	*iter;
	t_vec3		color;
	t_vec3		p_hit;
	t_vec3		n_hit;
	t_vec3		p_hit_biais;
	t_vec3		light;
	t_f64		t0;
	t_f64		t1;
	t_f64		light_dist;
	int			shadow;

	vec3_set(&color, 0., 0., 0.);
	compute_hit(orig, dir, obj, &n_hit, &p_hit, t);
	compute_biais(&n_hit, &p_hit, &p_hit_biais);
	iter_light = objects;
	while (iter_light != NULL)
	{
		if (iter_light->object->type == LIGHT)
		{
			vec3_cpy(&light, &(iter_light->object->pos));
			vec3_sub(&light, &p_hit);
			light_dist = vec3_len(&light);
			vec3_norm(&light);
			shadow = 0;
			iter = objects;
			while (iter != NULL)
			{
				if (iter_light != iter)
				{
					if (iter->object->type == SPHERE && 
						intersect_sphere(&p_hit_biais, &light, 
							iter->object, &t0, &t1) == SUCCESS)
					{
						shadow = 1;
						break ;
					}
					else if (iter->object->type == PLANE &&
						intersect_plane(&p_hit_biais, &light, 
							iter->object, &t0) == SUCCESS)
					{
						if (t0 < light_dist)
						{
							shadow = 1;
							break ;
						}
					}
					else if (iter->object->type == CYLIND && 
						intersect_cylinder(&p_hit_biais, &light, 
							iter->object, &t0, &t1) == SUCCESS)
					{

						shadow = 1;
						break ;
					}
				}
				iter = iter->next;
			}
			if (shadow == 0)
				mix_color(&color, &(obj->color), &(iter_light->object->e_color), 
							vec3_dot(&n_hit, &light));
		}
		iter_light = iter_light->next;
	}
	vec3_add(&color, &(obj->e_color));
	return (convert_color(&color));
}

static t_object	*trace(t_vec3 *orig, t_vec3 *dir, t_obj_lst *objects, t_f64 *t)
{
	t_obj_lst	*iter;
	t_object	*obj;
	t_f64		t0;
	t_f64		t1;

	iter = objects;
	*t = FLOAT_INF;
	obj = NULL;
	while (iter != NULL)
	{
		if (iter->object->type == SPHERE && intersect_sphere(orig, dir, iter->object, &t0, &t1) == SUCCESS)
		{
			if (t0 < *t)
			{
				*t = t0;
				obj = iter->object;
			}
		}
		else if (iter->object->type == PLANE && intersect_plane(orig, dir,
				iter->object, &t0) == SUCCESS)
		{
			if (t0 < *t)
			{
				*t = t0;
				obj = iter->object;
			}
		}
		else if (iter->object->type == CYLIND && intersect_cylinder(orig, dir,
				iter->object, &t0, &t1) == SUCCESS)
		{
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

/*
**	CameraSpace = Convert pixel to screen (ration, fov [-1:1])
**	Ray origin : (0, 0, 0)
**	Ray dir = CameraSpace - Ray origin
**	Ray dir = normalize
**	Trace ray
*/

static void		draw_start(t_vec3 *dir, int i, int j, t_data *data)
{
	t_object	*obj;
	t_color		color;
	t_vec3		orig;
	t_f64		t;

	vec3_set(&orig, 0, 10, 20);
	vec3_norm(dir);
	obj = trace(&orig, dir, data->env.objects, &t);
	if (obj != NULL && obj->type != LIGHT)
	{
		color = compute_color(&orig, dir, obj,
			data->env.objects, t);
		ft_mlx_put(&(data->mlx), j, i, color);
	}
}

int				draw_rt(void *data)
{
	t_algo		*algo;
	t_vec3		camera;
	t_matrix	rot;
	int			i;
	int			j;

	algo = (t_algo *)data;
	i = algo->start;
	rot = matrix_rot(&(algo->data->env.ang));
	while (i < algo->end)
	{
		j = 0;
		while (j < algo->data->env.width)
		{
			pixel_to_screen(j, i, &camera, &(algo->data->env));
			matrix_mul3_vec3(rot, &camera);
			draw_start(&camera, i, j, algo->data);
			j++;
		}
		i++;
	}
	matrix_del(MATRIX_33, &rot);
	return (SUCCESS);
}
