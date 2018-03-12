/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:22:50 by vparis            #+#    #+#             */
/*   Updated: 2018/03/12 13:04:56 by vparis           ###   ########.fr       */
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
** PHONG model : sum(La + sumLight(Ldi + Lsi)) * objectColor
** La (ambient) + Ld (Lambertian diffuse) + Ls (object constant specular)
*/

void			mix_color(t_vec3 *color, t_f64 dist, t_object *obj,
	t_object *light, t_vec3 *l, t_vec3 *n, t_vec3 *v)
{
	t_vec3	r;
	t_f64	t;
	t_f64	dln;
	t_vec3	vs;
	t_vec3	vd;
	t_vec3	light_intensity;

	vec3_cpy(&light_intensity, &(light->intensity));
	if (dist > 1.0)
	{
		t = exp(-0.5 * (dist / L_DIST_FACTOR));
		vec3_mul_scalar(&light_intensity, t);
	}
	dln = vec3_dot(n, l);
	if (dln < 0.0)
		dln = 0.0;
	vec3_cpy(&vd, &light_intensity);
	vec3_mul_scalar(&vd, dln * obj->phong[PHONG_KD]);
	if (obj->phong[PHONG_SHINI] > 0.0 && dln > 0.0)
	{
		vec3_cpy(&r, n);
		vec3_mul_scalar(&r, 2.0 * dln);
		vec3_sub(&r, l);
		vec3_norm(&r);
		t = fabs(vec3_dot(&r, v));
		if (t > INTER_MIN)
		{
			t = pow(t, obj->phong[PHONG_SHINI]) * obj->phong[PHONG_KS];
			vec3_cpy(&vs, &light_intensity);
			vec3_mul_scalar(&vs, t);
			vec3_add(&vd, &vs);
		}
	}
	vec3_add(color, &vd);
}

void			compute_biais(t_ray *ray_hit, t_vec3 *p_hit_biais)
{
	vec3_cpy(p_hit_biais, &(ray_hit->dir));
	vec3_mul_scalar(p_hit_biais, BIAIS);
	vec3_add(p_hit_biais, &(ray_hit->orig));
}

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
	else if (obj->type == CYLIND)
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

static t_color	compute_color(t_ray *ray, t_object *obj, t_obj_lst *objects,
								t_f64 t)
{
	t_obj_lst	*iter_light;
	t_obj_lst	*iter;
	t_vec3		color;
	t_vec3		p_hit_biais;
	t_f64		light_dist;
	t_solution	solution;
	t_ray		ray_hit;
	t_ray		ray_light;
	int			shadow;

	vec3_set(&color, obj->phong[PHONG_KA], obj->phong[PHONG_KA],
		obj->phong[PHONG_KA]);
	compute_hit(ray, &ray_hit, obj, t);
	compute_biais(&ray_hit, &p_hit_biais);
	if (vec3_dot(&(ray->dir), &(ray_hit.dir)) > 0.0)
		vec3_mul_scalar(&(ray_hit.dir), -1.0);
	iter_light = objects;
	while (iter_light != NULL)
	{
		if (iter_light->object->type == LIGHT)
		{
			vec3_cpy(&(ray_light.orig), &(iter_light->object->pos));
			vec3_sub(&(ray_light.orig), &(ray_hit.orig));
			light_dist = vec3_len(&(ray_light.orig));
			vec3_cpy(&(ray_light.dir), &(ray_light.orig));
			vec3_norm(&(ray_light.dir));
			vec3_cpy(&(ray_light.orig), &p_hit_biais);
			shadow = 0;
			iter = objects;
			while (iter != NULL)
			{
				if (iter_light != iter)
				{
					if (iter->object->type == SPHERE &&
						intersect_sphere(&ray_light, iter->object, &solution)
							== SUCCESS)
					{
						if (solution.t0 < light_dist && solution.t0 > 0.)
						{
							shadow = 1;
							break ;
						}
					}
					else if (iter->object->type == PLANE &&
						intersect_plane(&ray_light, iter->object, &solution)
							== SUCCESS)
					{
						if (solution.t0 < light_dist && solution.t0 > 0.)
						{
							shadow = 1;
							break ;
						}
					}
					else if (iter->object->type == CYLIND &&
						intersect_cylinder(&ray_light, iter->object, &solution)
							== SUCCESS)
					{
						if (solution.t0 < light_dist && solution.t0 > 0.)
						{
							shadow = 1;
							break ;
						}
					}
					else if (iter->object->type == CONE &&
						intersect_cone(&ray_light, iter->object, &solution)
							== SUCCESS)
					{
						if (solution.t0 < light_dist && solution.t0 > 0.)
						{
							shadow = 1;
							break ;
						}
					}
				}
				iter = iter->next;
			}
			if (shadow == 0)
				mix_color(&color, light_dist, obj, iter_light->object,
					&(ray_light.dir), &(ray_hit.dir), &(ray->dir));
		}
		iter_light = iter_light->next;
	}
	vec3_mul(&color, &(obj->color));
	return (convert_color(&color));
}

static t_object	*trace(t_ray *ray, t_obj_lst *objects, t_solution *solution)
{
	t_obj_lst	*iter;
	t_object	*obj;

	iter = objects;
	solution->t = FLOAT_INF;
	obj = NULL;
	while (iter != NULL)
	{
		if (iter->object->type == SPHERE && intersect_sphere(ray,
			iter->object, solution) == SUCCESS)
		{
			if (solution->t0 < solution->t)
			{
				solution->t = solution->t0;
				obj = iter->object;
			}
		}
		else if (iter->object->type == PLANE && intersect_plane(ray,
				iter->object, solution) == SUCCESS)
		{
			if (solution->t0 < solution->t)
			{
				solution->t = solution->t0;
				obj = iter->object;
			}
		}
		else if (iter->object->type == CYLIND && intersect_cylinder(ray,
				iter->object, solution) == SUCCESS)
		{
			if (solution->t0 < solution->t)
			{
				solution->t = solution->t0;
				obj = iter->object;
			}
		}
		else if (iter->object->type == CONE && intersect_cone(ray,
				iter->object, solution) == SUCCESS)
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

static void		draw_start(t_vec3 *dir, int i, int j, t_data *data)
{
	t_object	*obj;
	t_color		color;
	t_solution	solution;
	t_ray		ray;

	vec3_norm(dir);
	vec3_cpy(&(ray.dir), dir);
	vec3_cpy(&(ray.orig), &(data->env.cam_orig));
	obj = trace(&(ray), data->env.objects, &solution);
	if (obj != NULL && obj->type != LIGHT)
	{
		color = compute_color(&ray, obj, data->env.objects, solution.t);
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
			draw_start(&camera, i, j, algo->data);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
