/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:33:10 by vparis            #+#    #+#             */
/*   Updated: 2018/03/08 15:08:03 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "ft_math.h"
#include "matrix.h"

void			matrix_getsize(int type, int *l, int *c)
{
	*l = (type & MATRIX_L) >> 4;
	*c = type & MATRIX_C;
}

static void		matrix_set_rot_x(t_matrix rot, t_f64 ang)
{
	t_f64	c;
	t_f64	s;

	c = ft_cos(ang);
	s = ft_sin(ang);
	rot[0][0] = 1.;
	rot[0][1] = 0.;
	rot[0][2] = 0.;
	rot[1][0] = 0.;
	rot[1][1] = c;
	rot[1][2] = s;
	rot[2][0] = 0.;
	rot[2][1] = -s;
	rot[2][2] = c;
}

static void		matrix_set_rot_y(t_matrix rot, t_f64 ang)
{
	t_f64	c;
	t_f64	s;

	c = ft_cos(ang);
	s = ft_sin(ang);
	rot[0][0] = c;
	rot[0][1] = 0.;
	rot[0][2] = -s;
	rot[1][0] = 0.;
	rot[1][1] = 1.;
	rot[1][2] = 0.;
	rot[2][0] = s;
	rot[2][1] = 0.;
	rot[2][2] = c;
}

static void		matrix_set_rot_z(t_matrix rot, t_f64 ang)
{
	t_f64	c;
	t_f64	s;

	c = ft_cos(ang);
	s = ft_sin(ang);
	rot[0][0] = c;
	rot[0][1] = s;
	rot[0][2] = 0.;
	rot[1][0] = -s;
	rot[1][1] = c;
	rot[1][2] = 0.;
	rot[2][0] = 0.;
	rot[2][1] = 0.;
	rot[2][2] = 1.;
}

t_matrix		matrix_rot(t_vec3 *ang)
{
	t_matrix	rot;
	t_matrix	tmp;

	if ((rot = matrix_new(MATRIX_33, MATRIX_NOSET)) == NULL)
		return (NULL);
	if ((tmp = matrix_new(MATRIX_33, MATRIX_NOSET)) == NULL)
		return (NULL);
	matrix_set_rot_z(tmp, ang->z);
	matrix_set_rot_y(rot, ang->y);
	matrix_mul3(tmp, rot);
	matrix_set_rot_x(rot, ang->x);
	matrix_mul3(tmp, rot);
	matrix_del(MATRIX_33, &rot);
	return (tmp);
}

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