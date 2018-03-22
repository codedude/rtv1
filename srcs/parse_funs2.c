/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:31:31 by vparis            #+#    #+#             */
/*   Updated: 2018/03/22 17:10:39 by vparis           ###   ########.fr       */
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

int		parse_t_orig(t_env *env, char **strs)
{
	t_f64	n[3];

	if (ft_atof64_s(strs[0], &n[0]) == ERROR
		|| ft_atof64_s(strs[1], &n[1]) == ERROR
		|| ft_atof64_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	vec3_set(&(env->cam_orig),
		clamp_f64(n[0], -360.0, 360.0),
		clamp_f64(n[1], -360.0, 360.0),
		clamp_f64(n[2], -360.0, 360.0)
	);
	return (SUCCESS);
}

int		parse_t_pos(t_env *env, char **strs)
{

	return (SUCCESS);
}

int		parse_t_dir(t_env *env, char **strs)
{

	return (SUCCESS);
}

int		parse_t_size(t_env *env, char **strs)
{

	return (SUCCESS);
}

int		parse_t_color(t_env *env, char **strs)
{

	return (SUCCESS);
}

int		parse_t_intensity(t_env *env, char **strs)
{

	return (SUCCESS);
}

int		parse_t_phong(t_env *env, char **strs)
{

	return (SUCCESS);
}
