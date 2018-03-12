/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:33:10 by vparis            #+#    #+#             */
/*   Updated: 2018/03/12 11:54:15 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_math.h"
#include "matrix.h"

static void		matrix_set_rot_v(t_matrix rot, t_f64 ang, t_vec3 *v)
{
	t_f64	c;
	t_f64	c1;
	t_f64	s;

	c = ft_cos(ang);
	c1 = 1. - c;
	s = ft_sin(ang);
	rot[0][0] = c + v->x * v->x * c1;
	rot[0][1] = v->x * v->y * c1 - v->z * s;
	rot[0][2] = v->x * v->z * c1 + v->y * s;
	rot[1][0] = v->y * v->x * c1 + v->z * s;
	rot[1][1] = c + v->y * v->y * c1;
	rot[1][2] = v->y * v->z * c1 - v->x * s;
	rot[2][0] = v->z * v->x * c1 - v->y * s;
	rot[2][1] = v->z * v->y * c1 + v->x * s;
	rot[2][2] = c + v->z * v->z * c1;
}

t_matrix		matrix_rot_vec(t_f64 ang, t_vec3 *v)
{
	t_matrix	rot;

	if ((rot = matrix_new(MATRIX_33, MATRIX_NOSET)) == NULL)
		return (NULL);
	matrix_set_rot_v(rot, ang, v);
	return (rot);
}
