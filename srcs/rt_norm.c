/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_norm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:23:51 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 15:39:29 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_math.h"
#include "matrix.h"
#include "objects.h"
#include "rtv1.h"

void			norm_sphere(t_ray *ray_hit, t_object *obj)
{
	vec3_cpy(&(ray_hit->dir), &(ray_hit->orig));
	vec3_sub(&(ray_hit->dir), &(obj->pos));
	vec3_norm(&(ray_hit->dir));
}

void			norm_plane(t_ray *ray_hit, t_object *obj)
{
	vec3_cpy(&(ray_hit->dir), &(obj->norm));
}

void			norm_cylinder(t_ray *ray_hit, t_object *obj)
{
	t_vec3		tmp;
	t_matrix	rot;

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

void			norm_cone(t_ray *ray_hit, t_object *obj)
{
	t_f64	t;
	t_vec3	tmp;

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

void			compute_hit(t_ray *ray, t_ray *ray_hit, t_f64 t)
{
	t_vec3	tmp;

	vec3_cpy(&tmp, &(ray->dir));
	vec3_mul_scalar(&tmp, t);
	vec3_cpy(&(ray_hit->orig), &(ray->orig));
	vec3_add(&(ray_hit->orig), &tmp);
}
