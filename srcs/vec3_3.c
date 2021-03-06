/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:06:44 by vparis            #+#    #+#             */
/*   Updated: 2018/03/12 11:47:40 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "matrix.h"

void			vec3_mul_scalar(t_vec3 *v1, t_f64 r)
{
	v1->x *= r;
	v1->y *= r;
	v1->z *= r;
}

void			vec3_div_scalar(t_vec3 *v1, t_f64 r)
{
	v1->x /= r;
	v1->y /= r;
	v1->z /= r;
}

void			vec3_add_scalar(t_vec3 *v1, t_f64 s)
{
	v1->x += s;
	v1->y += s;
	v1->z += s;
}

void			vec3_sub_scalar(t_vec3 *v1, t_f64 s)
{
	v1->x -= s;
	v1->y -= s;
	v1->z -= s;
}
