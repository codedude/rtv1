/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:06:19 by vparis            #+#    #+#             */
/*   Updated: 2018/03/05 18:03:31 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "matrix.h"
#include "rtv1.h"

/*
** Convert pixel(int x, int y) to NDC
** Convert NDC(float x, float y) to SCREEN with aspect ratio and FOV [-1:1]
*/

void		pixel_to_screen(int x, int y, t_vec3 *camera, t_env *env)
{
	t_f64	fov;

	fov = ft_tan(FOV / 2.);
	camera->x = ((t_f64)x + 0.5) / (t_f64)env->width;
	camera->y = ((t_f64)y + 0.5) / (t_f64)env->height;
	if (env->ratio_dir == 1)
	{
		camera->x = (2 * camera->x - 1.) * fov;
		camera->y = (1. - 2 * camera->y) * fov;
	}
	else if (env->ratio_dir == -1)
	{
		camera->x = (2 * camera->x - 1.) * fov;
		camera->y = (1. - 2 * camera->y) * fov;
	}
	else
	{
		camera->x = (2 * camera->x - 1.) * fov;
		camera->y = (1. - 2 * camera->y) * fov;
	}
	camera->z = -1.;
}

/*
** Convert color from vector (t_vec3) to int (t_color)
*/

t_color		convert_color(t_vec3 *color)
{
	int	x;
	int	y;
	int	z;

	x = (unsigned char)((color->x < 1. ? color->x : 1.) * 255.);
	y = (unsigned char)((color->y < 1. ? color->y : 1.) * 255.);
	z = (unsigned char)((color->z < 1. ? color->z : 1.) * 255.);
	return (ft_mlx_getcolor(x, y, z));
}
