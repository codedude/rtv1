/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:22:50 by vparis            #+#    #+#             */
/*   Updated: 2018/03/12 18:11:50 by vparis           ###   ########.fr       */
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

void			compute_hit(t_ray *ray, t_ray *ray_hit, t_object *obj,
							t_f64 t)
{
	t_vec3		tmp;
	t_matrix	rot;

	vec3_cpy(&tmp, &(ray->dir));
	vec3_mul_scalar(&tmp, t);
	vec3_cpy(&(ray_hit->orig), &(ray->orig));
	vec3_add(&(ray_hit->orig), &tmp);
	if (obj->type == SPHERE)
	{
		vec3_cpy(&(ray_hit->dir), &(ray_hit->orig));
		vec3_sub(&(ray_hit->dir), &(obj->pos));
		vec3_norm(&(ray_hit->dir));
	}
	else if (obj->type == PLANE)
		vec3_cpy(&(ray_hit->dir), &(obj->norm));
	else if (obj->type == CYLINDER)
	{
		vec3_cpy(&tmp, &(obj->norm));
		vec3_cpy(&(ray_hit->dir), &(ray_hit->orig));
		vec3_sub(&(ray_hit->dir), &(obj->pos));
		rot = matrix_rot_vec(180., &tmp);
		matrix_mul3_vec3(rot, &(ray_hit->dir));
		matrix_del(MATRIX_33, &rot);
		vec3_add(&(ray_hit->dir), &(obj->pos));
		vec3_cpy(&tmp, &(ray_hit->dir));
		vec3_cpy(&(ray_hit->dir), &(ray_hit->orig));
		vec3_sub(&(ray_hit->dir), &tmp);
		vec3_norm(&(ray_hit->dir));
	}
	else if (obj->type == CONE)
	{
		vec3_cpy(&(ray_hit->dir), &(ray_hit->orig));
		vec3_sub(&(ray_hit->dir), &(obj->pos));
		t = ft_cos(2.0 * obj->radius);
		t = 1.0 + (1.0 - t) / (1.0 + t);
		t *= vec3_dot(&(ray_hit->dir), &(obj->norm));
		vec3_cpy(&tmp, &(ray_hit->orig));
		vec3_sub(&tmp, &(obj->pos));
		vec3_cpy(&(ray_hit->dir), &(obj->norm));
		vec3_mul_scalar(&(ray_hit->dir), -t);
		vec3_add(&(ray_hit->dir), &tmp);
		vec3_norm(&(ray_hit->dir));
	}
}

t_obj_lst		*find_next_light(t_obj_lst *lst)
{
	while (lst != NULL && !is_light(lst->object))
		lst = lst->next;
	return (lst);
}

t_obj_lst		*find_next_object(t_obj_lst *lst)
{
	while (lst != NULL && is_light(lst->object))
		lst = lst->next;
	return (lst);
}

/*
** Save p_hit_biais in ray.orig !!!
*/

t_color			compute_light(t_env *env, t_ray *ray, t_ray *ray_hit,
								t_object *obj)
{
	t_obj_lst	*iter_light;
	t_obj_lst	*iter_object;
	t_f64		light_dist;
	t_solution	solution;
	t_vec3		color;
	t_ray		ray_light;

	init_color(&color, obj);
	iter_light = env->objects;
	while ((iter_light = find_next_light(iter_light)) != NULL)
	{
		vec3_cpy(&(ray_light.orig), &(iter_light->object->pos));
		vec3_sub(&(ray_light.orig), &(ray_hit->orig));
		light_dist = vec3_len(&(ray_light.orig));
		vec3_cpy(&(ray_light.dir), &(ray_light.orig));
		vec3_norm(&(ray_light.dir));
		vec3_cpy(&(ray_light.orig), &(ray->orig));
		iter_object = env->objects;
		while ((iter_object = find_next_object(iter_object)) != NULL)
		{
			if (env->intersect[iter_object->object->type](&ray_light,
				iter_object->object, &solution) == SUCCESS)
				if (solution.t0 < light_dist && solution.t0 > 0.)
					break ;
			iter_object = iter_object->next;
		}
		if (iter_object == NULL)
			mix_color(&color, light_dist, obj, iter_light->object,
				&(ray_light.dir), &(ray_hit->dir), &(ray->dir));
		iter_light = iter_light->next;
	}
	vec3_mul(&color, &(obj->color));
	return (convert_color(&color));
}

static t_color	compute_color(t_env *env, t_ray *ray, t_object *obj, t_f64 t)
{
	t_color		color;
	t_vec3		p_hit_biais;
	t_ray		ray_hit;

	compute_hit(ray, &ray_hit, obj, t);
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
	obj = trace(&(data->env), &(ray), &solution);
	if (obj != NULL && obj->type != LIGHT)
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
