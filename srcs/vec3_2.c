/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:56:56 by vparis            #+#    #+#             */
/*   Updated: 2018/03/05 14:41:37 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "matrix.h"

t_f64			vec3_dot(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_f64			vec3_len(t_vec3 *v1)
{
	return (sqrt(v1->x * v1->x + v1->y * v1->y + v1->z * v1->z));
}

t_f64			vec3_len_ns(t_vec3 *v1)
{
	return (v1->x * v1->x + v1->y * v1->y + v1->z * v1->z);
}

void			vec3_norm(t_vec3 *v1)
{
	t_f64	len;

	len = vec3_len_ns(v1);
	if (len > 0.)
	{
		len = 1. / sqrt(len);
		v1->x *= len;
		v1->y *= len;
		v1->z *= len;
	}
}

t_vec3			*vec3_cross(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	*tmp;

	if ((tmp = vec3_new()) == NULL)
		return (NULL);
	tmp->x = v1->y * v2->z - v1->z * v2->y;
	tmp->y = v1->z * v2->x - v1->x * v2->z;
	tmp->z = v1->x * v2->y - v1->y * v2->x;
	return (tmp);
}
