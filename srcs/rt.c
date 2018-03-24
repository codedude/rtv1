/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:22:50 by vparis            #+#    #+#             */
/*   Updated: 2018/03/24 23:04:20 by valentin         ###   ########.fr       */
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
** Save p_hit_biais in ray.orig !!!
*/

t_color			compute_light(t_env *env, t_ray *ray, t_ray *ray_hit,
								t_object *obj)
{
	t_obj_lst	*iter_light;
	t_solution	solution;
	t_vec3		color;
	t_ray		ray_light;
	t_vec3		intensity;

	color_ambient(&color, obj);
	iter_light = env->objects;
	while ((iter_light = find_next_light(iter_light)) != NULL)
	{
		solution.t = compute_raylight(ray, ray_hit, &ray_light,
			iter_light->object);
		if (is_shadow(env, &ray_light, &solution) == ERROR)
		{
			color_intensity(&intensity, iter_light->object, solution.t);
			solution.t = vec3_dot(&(ray_hit->dir), &(ray_light.dir));
			if (color_diffuse(&intensity, &color, obj, &(solution.t))
				== SUCCESS && obj->phong[PHONG_SHINI] > 0.0)
				color_specular(&intensity, &color, obj,
					compute_reflect_ray(&(ray->dir), &(ray_hit->dir),
						&(ray_light.dir), solution.t));
		}
		iter_light = iter_light->next;
	}
	return (convert_color(&color, &(obj->color)));
}

static t_color	compute_color(t_env *env, t_ray *ray, t_object *obj, t_f64 t)
{
	t_color		color;
	t_vec3		p_hit_biais;
	t_ray		ray_hit;

	compute_hit(ray, &ray_hit, t);
	env->norm[obj->type](&ray_hit, obj);
	compute_biais(&ray_hit, &p_hit_biais);
	if (vec3_dot(&(ray->dir), &(ray_hit.dir)) > 0.0)
		vec3_mul_scalar(&(ray_hit.dir), -1.0);
	vec3_cpy(&(ray->orig), &p_hit_biais);
	color = compute_light(env, ray, &ray_hit, obj);

	return (color);
}

static t_object	*trace(t_env *env, t_ray *ray, t_solution *solution)
{
	t_obj_lst	*iter;
	t_object	*obj;

	solution->t = FLOAT_INF;
	obj = NULL;
	iter = env->objects;
	while ((iter = find_next_object(iter)) != NULL)
	{
		if (env->intersect[iter->object->type](ray, iter->object, solution)
			== SUCCESS)
		{
			if (solution->t0 < solution->t)
			{
				solution->t = solution->t0;
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

static void		draw_start(t_data *data, t_vec3 *dir, int i, int j)
{
	t_object	*obj;
	t_color		color;
	t_solution	solution;
	t_ray		ray;

	vec3_norm(dir);
	vec3_cpy(&(ray.dir), dir);
	vec3_cpy(&(ray.orig), &(data->env.cam_orig));
	obj = trace(&(data->env), &ray, &solution);
	if (obj != NULL)
	{
		color = compute_color(&(data->env), &ray, obj, solution.t);
		ft_mlx_put(&(data->mlx), j, i, color);
	}
}

int				draw_rt(void *data)
{
	t_algo		*algo;
	t_vec3		camera;
	int			i;
	int			j;

	algo = (t_algo *)data;
	i = algo->start;
	while (i < algo->end)
	{
		j = 0;
		while (j < algo->data->env.width)
		{
			pixel_to_screen(j, i, &camera, &(algo->data->env));
			matrix_mul3_vec3(algo->data->env.rot, &camera);
			draw_start(algo->data, &camera, i, j);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
