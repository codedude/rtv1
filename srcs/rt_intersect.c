/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:08:48 by vparis            #+#    #+#             */
/*   Updated: 2018/03/08 22:13:53 by valentin         ###   ########.fr       */
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

int		intersect_sphere(t_vec3 *orig, t_vec3 *dir, t_object *obj,
									t_f64 *t0, t_f64 *t1)
{
	t_f64		tca;
	t_f64		d2;
	t_f64		thc;
	t_vec3		l;

	vec3_cpy(&l, &(obj->pos));
	vec3_sub(&l, orig);
	tca = vec3_dot(&l, dir);
	if (tca < 0.)
		return (ERROR);
	d2 = obj->radius2 - (vec3_dot(&l, &l) - tca * tca);
	if (d2 < 0.)
		return (ERROR);
	if (d2 == 0.)
		*t0 = tca;
	else
	{
		thc = sqrt(d2);
		*t0 = tca - thc;
		*t1 = tca + thc;
	}
	if (*t0 < INTER_MIN)
		*t0 = *t1;
	return (SUCCESS);
}

int		intersect_plane(t_vec3 *orig, t_vec3 *dir, t_object *obj, t_f64 *t)
{
	t_f64	denom;
	t_vec3	diff;

	denom = vec3_dot(&(obj->norm), dir);
	if (fabs(denom) > INTER_MIN)
	{
		vec3_cpy(&diff, &(obj->pos));
		vec3_sub(&diff, orig);
		*t = vec3_dot(&diff, &(obj->norm)) / denom;
		return (*t > INTER_MIN ? SUCCESS : ERROR);
	}
	return (ERROR);
}

int		intersect_cylinder(t_vec3 *orig, t_vec3 *dir, t_object *obj,
									t_f64 *t0, t_f64 *t1)
{
	t_vec3	delta_p;
	t_vec3	vva;
	t_vec3	dpva;
	t_vec3	tmp;
	t_vec3	tmp2;
	t_f64	abc[4];

	//delta p
	vec3_cpy(&delta_p, orig);
	vec3_sub(&delta_p, &(obj->pos));
	//va
	vec3_cpy(&tmp, &(obj->norm));
	//(v,va)va
	vec3_cpy(&vva, &tmp);
	vec3_mul_scalar(&vva, vec3_dot(dir, &tmp));
	//(delta p,va)va
	vec3_cpy(&dpva, &tmp);
	vec3_mul_scalar(&dpva, vec3_dot(&delta_p, &tmp));
	//A dot(v - vva)
	vec3_cpy(&tmp, dir);
	vec3_sub(&tmp, &vva);
	abc[0] = vec3_dot(&tmp, &tmp);
	//B
	vec3_cpy(&tmp2, &delta_p);
	vec3_sub(&tmp2, &dpva);
	abc[1] = 2. * vec3_dot(&tmp, &tmp2);
	//C
	abc[2] = vec3_dot(&tmp2, &tmp2) - obj->radius2;

	//Find t1 and t2
	abc[3] = abc[1] * abc[1] - (4. * abc[0] * abc[2]);
	if (abc[3] < 0.)
		return (ERROR);

	if (abc[3] == 0.)
		*t0 = -abc[1] / (2. * abc[0]);
	else
	{
		abc[3] = sqrt(abc[3]);
		*t0 = (-abc[1] + abc[3]) / (2. * abc[0]);
		*t1 = (-abc[1] - abc[3]) / (2. * abc[0]);
	}
	//Check + values
	if (*t0 < INTER_MIN && *t1 < INTER_MIN)
		return (ERROR);
	if (*t0 < INTER_MIN)
		*t0 = *t1;
	else if (*t1 >= INTER_MIN && *t1 < *t0)
		*t0 = *t1;
	return (SUCCESS);
}

int		intersect_cone(t_vec3 *orig, t_vec3 *dir, t_object *obj,
									t_f64 *t0, t_f64 *t1)
{
	t_vec3	delta_p;
	t_vec3	va;
	t_vec3	vva;
	t_vec3	vpva;
	t_vec3	tmp;
	t_vec3	tmp2;
	t_f64	abc[4];
	t_f64	cos2;
	t_f64	sin2;
	t_f64	dvva;
	t_f64	dpva;

	cos2 = (1. + ft_cos(2. * obj->radius)) / 2.;
	sin2 = (1. - ft_cos(2. * obj->radius)) / 2.;
	//delta p
	vec3_cpy(&delta_p, orig);
	vec3_sub(&delta_p, &(obj->pos));
	//va
	vec3_cpy(&va, &(obj->norm));
	dvva = vec3_dot(dir, &va);
	//(v,va)va
	vec3_cpy(&vva, &va);
	vec3_mul_scalar(&vva, dvva);
	//(delta p,va)va
	vec3_cpy(&vpva, &va);
	dpva = vec3_dot(&delta_p, &va);
	vec3_mul_scalar(&vpva, dpva);
	//A dot(v - vva)
	vec3_cpy(&tmp, dir);
	vec3_sub(&tmp, &vva);
	abc[0] = cos2 * vec3_dot(&tmp, &tmp) - sin2 * dvva * dvva;
	//B
	vec3_cpy(&tmp2, &delta_p);
	vec3_sub(&tmp2, &vpva);
	abc[1] = 2. * cos2 * vec3_dot(&tmp, &tmp2) - 2. * sin2 * dvva * dpva;
	//C
	abc[2] = cos2 * vec3_dot(&tmp2, &tmp2) - sin2 * dpva * dpva;

	//Find t1 and t2
	abc[3] = abc[1] * abc[1] - (4. * abc[0] * abc[2]);
	if (abc[3] == 0.)
		*t0 = -abc[1] / (2. * abc[0]);
	else
	{
		abc[3] = sqrt(abc[3]);
		*t0 = (-abc[1] + abc[3]) / (2. * abc[0]);
		*t1 = (-abc[1] - abc[3]) / (2. * abc[0]);
	}
	//Check + values
	if (*t0 < 0. && *t1 < 0.)
		return (ERROR);
	if (*t0 < 0.)
		*t0 = *t1;
	else if (*t1 >= 0. && *t1 < *t0)
		*t0 = *t1;
	return (SUCCESS);
}