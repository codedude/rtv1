/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:56:49 by valentin          #+#    #+#             */
/*   Updated: 2018/04/03 14:35:43 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "objects.h"
#include "matrix.h"

void		object_set_intensity(t_object *obj, t_vec3 *intensity)
{
	vec3_set(&(obj->intensity),
		clamp_f64(intensity->x, 0.0, 5.0),
		clamp_f64(intensity->y, 0.0, 5.0),
		clamp_f64(intensity->z, 0.0, 5.0));
}

void		object_set_color(t_object *obj, t_vec3 *color)
{
	vec3_set(&(obj->color),
		(t_f64)clamp_i32(color->x, 0, 255) / 255.,
		(t_f64)clamp_i32(color->y, 0, 255) / 255.,
		(t_f64)clamp_i32(color->z, 0, 255) / 255.);
}

void		object_set_radius(t_object *obj, t_f64 radius)
{
	obj->radius = clamp_f64(radius, 0.001, 10000.0);
	obj->radius2 = obj->radius * obj->radius;
}

void		object_set_phong(t_object *obj, t_f64 phong[PHONGS])
{
	obj->phong[PHONG_SHINI] = round(clamp_f64(phong[PHONG_SHINI], 0.0, 1200.0));
	obj->phong[PHONG_KA] = clamp_f64(phong[PHONG_KA], 0.0, 1.0);
	obj->phong[PHONG_KD] = clamp_f64(phong[PHONG_KD], 0.0, 1.0);
	obj->phong[PHONG_KS] = clamp_f64(phong[PHONG_KS], 0.0, 1.0);
}
