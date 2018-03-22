/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:30:20 by vparis            #+#    #+#             */
/*   Updated: 2018/03/22 17:27:24 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "libft.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "rtv1.h"
#include "matrix.h"
#include "objects.h"

int		parse_t_width(t_env *env, char **strs)
{
	int		n;

	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	env->width = clamp_i32(n, 1, 2560);
	return (SUCCESS);
}

int		parse_t_height(t_env *env, char **strs)
{
	int		n;

	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	env->height = clamp_i32(n, 1, 1440);
	return (SUCCESS);
}

int		parse_t_background(t_env *env, char **strs)
{
	int	n[3];

	if (ft_atoi_s(strs[0], &n[0]) == ERROR
		|| ft_atoi_s(strs[1], &n[1]) == ERROR
		|| ft_atoi_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	env->background = ft_mlx_getcolor(
		clamp_i32(n[0], 0, 255),
		clamp_i32(n[1], 0, 255),
		clamp_i32(n[2], 0, 255)
	);
	return (SUCCESS);
}

int		parse_t_ang(t_env *env, char **strs)
{
	t_f64	n[3];

	if (ft_atof64_s(strs[0], &n[0]) == ERROR
		|| ft_atof64_s(strs[1], &n[1]) == ERROR
		|| ft_atof64_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	vec3_set(&(env->cam_ang),
		clamp_f64(n[0], -360.0, 360.0),
		clamp_f64(n[1], -360.0, 360.0),
		clamp_f64(n[2], -360.0, 360.0)
	);
	return (SUCCESS);
}

int		parse_t_fov(t_env *env, char **strs)
{
	int		n;
	
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	env->fov = (t_f64)clamp_f64(n, 1, 180);
	return (SUCCESS);
}
