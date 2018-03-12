/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 11:47:32 by vparis            #+#    #+#             */
/*   Updated: 2018/03/12 11:48:10 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "matrix.h"

void			vec3_add(t_vec3 *v1, t_vec3 *v2)
{
	v1->x += v2->x;
	v1->y += v2->y;
	v1->z += v2->z;
}

void			vec3_sub(t_vec3 *v1, t_vec3 *v2)
{
	v1->x -= v2->x;
	v1->y -= v2->y;
	v1->z -= v2->z;
}

void			vec3_mul(t_vec3 *v1, t_vec3 *v2)
{
	v1->x *= v2->x;
	v1->y *= v2->y;
	v1->z *= v2->z;
}

void			vec3_div(t_vec3 *v1, t_vec3 *v2)
{
	v1->x /= v2->x;
	v1->y /= v2->y;
	v1->z /= v2->z;
}
