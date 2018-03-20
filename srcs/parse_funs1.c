/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:30:20 by vparis            #+#    #+#             */
/*   Updated: 2018/03/20 18:11:46 by vparis           ###   ########.fr       */
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
	env->width = n;
	return (SUCCESS);
}

int		parse_t_height(t_env *env, char **strs)
{
	int		n;

	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	env->height = n;
	return (SUCCESS);
}

int		parse_t_background(t_env *env, char **strs)
{

	return (SUCCESS);
}

int		parse_t_ang(t_env *env, char **strs)
{

	return (SUCCESS);
}

int		parse_t_fov(t_env *env, char **strs)
{
	int		n;
	
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	env->fov = (t_f64)n;
	return (SUCCESS);
}
