/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:39:36 by vparis            #+#    #+#             */
/*   Updated: 2018/03/12 16:40:39 by vparis           ###   ########.fr       */
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
	vec3_mul_scalar(&r, 2.0 * dln);
	vec3_sub(&r, l);
	vec3_norm(&r);
	return (fabs(vec3_dot(&r, v)));
}

void			mix_color(t_vec3 *color, t_f64 dist, t_object *obj,
	t_object *light, t_vec3 *l, t_vec3 *n, t_vec3 *v)
{
	t_f64	t;
	t_vec3	vs;
	t_vec3	vd;
	t_vec3	light_intensity;

	vec3_cpy(&light_intensity, &(light->intensity));
	if (dist > 1.0)
	{
		t = exp(dist / L_DIST_FACTOR);
		vec3_mul_scalar(&light_intensity, t);
	}
	t = vec3_dot(n, l);
	if (t < 0.0)
		t = 0.0;
	vec3_cpy(&vd, &light_intensity);
	vec3_mul_scalar(&vd, t * obj->phong[PHONG_KD]);
	if (obj->phong[PHONG_SHINI] > 0.0 && t > 0.0)
		if ((t = compute_reflect_ray(v, n, l, t)) > INTER_MIN)
		{
			t = pow(t, obj->phong[PHONG_SHINI]) * obj->phong[PHONG_KS];
			vec3_cpy(&vs, &light_intensity);
			vec3_mul_scalar(&vs, t);
			vec3_add(&vd, &vs);
		}
	vec3_add(color, &vd);
}

void			init_color(t_vec3 *color, t_object *obj)
{
	vec3_set(color, obj->phong[PHONG_KA], obj->phong[PHONG_KA],
	obj->phong[PHONG_KA]);
}

int				is_light(t_object *obj)
{
	return (obj->intensity.x > 0.0 || obj->intensity.y > 0.0
			|| obj->intensity.z > 0.0);
}
