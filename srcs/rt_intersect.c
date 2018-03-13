/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:08:48 by vparis            #+#    #+#             */
/*   Updated: 2018/03/13 13:44:51 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_mlx.h"
#include "matrix.h"
#include "rtv1.h"
#include <math.h>
#include "libft.h"
#include "ft_math.h"

/*
** HIT = SUCCESS
*/

int		intersect_sphere(t_ray *ray, t_object *obj, t_solution *solution)
{
	t_f64		tca;
	t_f64		d2;
	t_f64		thc;
	t_vec3		l;

	vec3_cpy(&l, &(obj->pos));
	vec3_sub(&l, &(ray->orig));
	tca = vec3_dot(&l, &(ray->dir));
	if (tca < 0.)
		return (ERROR);
	d2 = obj->radius2 - (vec3_dot(&l, &l) - tca * tca);
	if (d2 < 0.)
		return (ERROR);
	if (d2 == 0.)
		solution->t0 = tca;
	else
	{
		thc = sqrt(d2);
		solution->t0 = tca - thc;
		solution->t1 = tca + thc;
	}
	if (solution->t0 < INTER_MIN)
		solution->t0 = solution->t1;
	return (SUCCESS);
}

int		intersect_plane(t_ray *ray, t_object *obj, t_solution *solution)
{
	t_f64	denom;
	t_vec3	diff;

	denom = vec3_dot(&(obj->norm), &(ray->dir));
	if (fabs(denom) > INTER_MIN)
	{
		vec3_cpy(&diff, &(obj->pos));
		vec3_sub(&diff, &(ray->orig));
		solution->t0 = vec3_dot(&diff, &(obj->norm)) / denom;
		return (solution->t0 > 0. ? SUCCESS : ERROR);
	}
	return (ERROR);
}

int		solve_quadra(t_f64 abc[3], t_solution *solution)
{
	t_f64	r;

	r = abc[1] * abc[1] - (4. * abc[0] * abc[2]);
	if (r < 0.)
		return (ERROR);
	if (r == 0.)
		solution->t0 = -abc[1] / (2. * abc[0]);
	else
	{
		r = sqrt(r);
		solution->t0 = (-abc[1] + r) / (2. * abc[0]);
		solution->t1 = (-abc[1] - r) / (2. * abc[0]);
	}
	if (solution->t0 < INTER_MIN && solution->t1 < INTER_MIN)
		return (ERROR);
	if (solution->t0 < INTER_MIN)
		solution->t0 = solution->t1;
	else if (solution->t1 >= INTER_MIN && solution->t1 < solution->t0)
		solution->t0 = solution->t1;
	return (SUCCESS);
}

/*
**	//delta p
**	vec3_cpy(&delta_p, &(ray->orig));
**	vec3_sub(&delta_p, &(obj->pos));
**	//va
**	vec3_cpy(&tmp, &(obj->norm));
**	//(v,va)va
**	vec3_cpy(&vva, &tmp);
**	vec3_mul_scalar(&vva, vec3_dot(&(ray->dir), &tmp));
**	//(delta p,va)va
**	vec3_cpy(&dpva, &tmp);
**	vec3_mul_scalar(&dpva, vec3_dot(&delta_p, &tmp));
** END : delta_p = tmp2
*/

int		intersect_cylinder(t_ray *ray, t_object *obj, t_solution *solution)
{
	t_vec3	delta_p;
	t_vec3	vva;
	t_vec3	dpva;
	t_vec3	tmp;
	t_f64	abc[3];

	vec3_cpy(&delta_p, &(ray->orig));
	vec3_sub(&delta_p, &(obj->pos));
	vec3_cpy(&tmp, &(obj->norm));
	vec3_cpy(&vva, &tmp);
	vec3_mul_scalar(&vva, vec3_dot(&(ray->dir), &tmp));
	vec3_cpy(&dpva, &tmp);
	vec3_mul_scalar(&dpva, vec3_dot(&delta_p, &tmp));
	vec3_cpy(&tmp, &(ray->dir));
	vec3_sub(&tmp, &vva);
	abc[0] = vec3_dot(&tmp, &tmp);
	vec3_sub(&delta_p, &dpva);
	abc[1] = 2. * vec3_dot(&tmp, &delta_p);
	abc[2] = vec3_dot(&delta_p, &delta_p) - obj->radius2;
	return (solve_quadra(abc, solution));
}

/*
** vec[0] = delta_p
** vec[1] = vva
** vec[2] = vpva
** vec[3] = tmp
**	//delta p
**	vec3_cpy(&delta_p, &(ray->orig));
**	vec3_sub(&delta_p, &(obj->pos));
**	//va
**	vec3_cpy(&va, &(obj->norm));
**	dvva = vec3_dot(&(ray->dir), &va);
**	//(v,va)va
**	vec3_cpy(&vva, &va);
**	vec3_mul_scalar(&vva, dvva);
**	//(delta p,va)va
**	vec3_cpy(&vpva, &va);
**	dpva = vec3_dot(&delta_p, &va);
**	vec3_mul_scalar(&vpva, dpva);
** END : delta_p = tmp2
*/

int		intersect_cone(t_ray *ray, t_object *obj, t_solution *solution)
{
	t_vec3	vec[4];
	t_f64	abc[3];
	t_f64	cos2sin2[2];
	t_f64	dvpva[2];

	cos2sin2[0] = (1. + ft_cos(2. * obj->radius)) / 2.;
	cos2sin2[1] = (1. - ft_cos(2. * obj->radius)) / 2.;
	vec3_cpy(&vec[0], &(ray->orig));
	vec3_sub(&vec[0], &(obj->pos));
	dvpva[0] = vec3_dot(&(ray->dir), &(obj->norm));
	vec3_cpy(&vec[1], &(obj->norm));
	vec3_mul_scalar(&vec[1], dvpva[0]);
	vec3_cpy(&vec[2], &(obj->norm));
	dvpva[1] = vec3_dot(&vec[0], &(obj->norm));
	vec3_mul_scalar(&vec[2], dvpva[1]);
	vec3_cpy(&vec[3], &(ray->dir));
	vec3_sub(&vec[3], &vec[1]);
	abc[0] = cos2sin2[0] * vec3_dot(&vec[3], &vec[3])
			- cos2sin2[1] * dvpva[0] * dvpva[0];
	vec3_sub(&vec[0], &vec[2]);
	abc[1] = 2. * cos2sin2[0] * vec3_dot(&vec[3], &vec[0])
			- 2. * cos2sin2[1] * dvpva[0] * dvpva[1];
	abc[2] = cos2sin2[0] * vec3_dot(&vec[0], &vec[0])
			- cos2sin2[1] * dvpva[1] * dvpva[1];
	return (solve_quadra(abc, solution));
}
