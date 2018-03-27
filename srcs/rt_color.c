/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:39:36 by vparis            #+#    #+#             */
/*   Updated: 2018/03/27 14:27:04 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
** light_dist_fact = exp(-0.5 * (dist / 100))
** t = t, dln and tmp
*/

t_f64			compute_reflect_ray(t_vec3 *v, t_vec3 *n, t_vec3 *l, t_f64 dln)
{
	t_vec3	r;

	vec3_cpy(&r, n);
	vec3_mul_scalar(&r, -2.0 * dln);
	vec3_add(&r, l);
	vec3_norm(&r);
	return (vec3_dot(&r, v));
}

void			color_intensity(t_vec3 *intensity, t_object *light, t_f64 dist)
{
	t_f64	t;

	vec3_cpy(intensity, &(light->intensity));
	if (dist > 1.0)
	{
		t = exp(dist / L_DIST_FACTOR);
		vec3_mul_scalar(intensity, t);
	}
}

int				color_diffuse(t_vec3 *intensity, t_vec3 *color, t_object *obj,
								t_f64 *t)
{
	t_vec3	vd;

	if (*t < 0.0)
		*t = 0.0;
	else
	{
		vec3_cpy(&vd, intensity);
		vec3_mul_scalar(&vd, *t * obj->phong[PHONG_KD]);
		vec3_add(color, &vd);
	}
	return (*t > 0.0 ? SUCCESS : ERROR);
}

void			color_specular(t_vec3 *intensity, t_vec3 *color, t_object *obj,
								t_f64 t)
{
	t_vec3	vs;

	if (t > 0.0)
	{
		t = pow(t, obj->phong[PHONG_SHINI]) * obj->phong[PHONG_KS];
		vec3_cpy(&vs, intensity);
		vec3_mul_scalar(&vs, t);
		vec3_add(color, &vs);
	}
}

void			color_ambient(t_vec3 *color, t_object *obj)
{
	vec3_set(color, obj->phong[PHONG_KA], obj->phong[PHONG_KA],
	obj->phong[PHONG_KA]);
}
