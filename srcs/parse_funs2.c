/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:31:31 by vparis            #+#    #+#             */
/*   Updated: 2018/03/27 14:26:24 by vparis           ###   ########.fr       */
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

int		parse_t_pos(void *data, char **strs)
{
	t_object	*obj;
	t_vec3		pos;

	obj = (t_object *)data;
	if (ft_atof64_s(strs[0], &pos.x) == ERROR
		|| ft_atof64_s(strs[1], &pos.y) == ERROR
		|| ft_atof64_s(strs[2], &pos.z) == ERROR)
		return (ERROR);
	object_set_pos(obj, &pos);
	return (SUCCESS);
}

int		parse_t_dir(void *data, char **strs)
{
	t_object	*obj;
	t_vec3		pos;

	obj = (t_object *)data;
	if (ft_atof64_s(strs[0], &pos.x) == ERROR
		|| ft_atof64_s(strs[1], &pos.y) == ERROR
		|| ft_atof64_s(strs[2], &pos.z) == ERROR)
		return (ERROR);
	object_set_dir(obj, &pos);
	return (SUCCESS);
}

int		parse_t_size(void *data, char **strs)
{
	t_object	*obj;
	t_f64		size;

	obj = (t_object *)data;
	if (ft_atof64_s(strs[0], &size) == ERROR)
		return (ERROR);
	object_set_radius(obj, size);
	return (SUCCESS);
}

int		parse_t_color(void *data, char **strs)
{
	t_object	*obj;
	int			n[3];
	t_vec3		pos;

	obj = (t_object *)data;
	if (ft_atoi_s(strs[0], &n[0]) == ERROR
		|| ft_atoi_s(strs[1], &n[1]) == ERROR
		|| ft_atoi_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	vec3_set(&pos, (t_f64)n[0], (t_f64)n[1], (t_f64)n[2]);
	object_set_color(obj, &pos);
	return (SUCCESS);
}

int		parse_t_intensity(void *data, char **strs)
{
	t_object	*obj;
	t_vec3		pos;

	obj = (t_object *)data;
	if (ft_atof64_s(strs[0], &pos.x) == ERROR
		|| ft_atof64_s(strs[1], &pos.y) == ERROR
		|| ft_atof64_s(strs[2], &pos.z) == ERROR)
		return (ERROR);
	object_set_intensity(obj, &pos);
	return (SUCCESS);
}
