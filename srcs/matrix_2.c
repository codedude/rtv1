/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:33:10 by vparis            #+#    #+#             */
/*   Updated: 2018/03/12 11:54:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
