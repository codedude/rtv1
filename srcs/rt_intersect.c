/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:08:48 by vparis            #+#    #+#             */
/*   Updated: 2018/03/05 18:51:13 by vparis           ###   ########.fr       */
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
	d2 = vec3_dot(&l, &l) - tca * tca;
	if (d2 > obj->radius2) 
		return (ERROR);
	thc = sqrt(obj->radius2 - d2);
	*t0 = tca - thc;
	*t1 = tca + thc; 
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