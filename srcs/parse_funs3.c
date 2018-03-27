/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 20:45:34 by vparis            #+#    #+#             */
/*   Updated: 2018/03/27 14:28:56 by vparis           ###   ########.fr       */
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

t_f64		clamp_f64(t_f64 f, t_f64 lmin, t_f64 lmax)
{
	if (f < lmin)
		return (lmin);
	else if (f > lmax)
		return (lmax);
	return (f);
}

int			clamp_i32(int f, int lmin, int lmax)
{
	if (f < lmin)
		return (lmin);
	else if (f > lmax)
		return (lmax);
	return (f);
}

static int	ft_atof64_s_divi(size_t len)
{
	int	divi;

	divi = 1;
	while (len--)
		divi *= 10;
	return (divi);
}

static void	compute_d(int d[2], char *str, t_f64 *n, int sign)
{
	int	divi;

	divi = ft_atof64_s_divi(ft_strlen(str));
	if (sign < 0)
		*n = (t_f64)d[0] - (t_f64)d[1] / (t_f64)divi;
	else
		*n = (t_f64)d[0] + (t_f64)d[1] / (t_f64)divi;
}

int			ft_atof64_s(char *str, t_f64 *n)
{
	char	**parts;
	int		d[2];
	int		sign;

	if ((parts = ft_strsplit(str, '.')) == NULL)
		return (ERROR);
	if (parts[1] == NULL)
	{
		ft_strsplit_free(parts);
		return (ERROR);
	}
	sign = (parts[0][0] == '-') ? -1 : 1;
	if (ft_atoi_s(parts[0], &d[0]) == ERROR
		|| ft_atoi_s(parts[1], &d[1]) == ERROR)
	{
		*n = ZERO_FLOAT;
		ft_strsplit_free(parts);
		return (ERROR);
	}
	else
		compute_d(d, parts[1], n, sign);
	ft_strsplit_free(parts);
	return (SUCCESS);
}

int			parse_t_orig(void *data, char **strs)
{
	t_env	*env;
	t_f64	n[3];

	env = (t_env *)data;
	if (ft_atof64_s(strs[0], &n[0]) == ERROR
		|| ft_atof64_s(strs[1], &n[1]) == ERROR
		|| ft_atof64_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	vec3_set(&(env->cam_orig), n[0], n[1], n[2]);
	return (SUCCESS);
}

int			parse_t_phong(void *data, char **strs)
{
	t_object	*obj;
	t_f64		phong[PHONGS];
	int			shini;

	obj = (t_object *)data;
	if (ft_atoi_s(strs[0], &shini) == ERROR
		|| ft_atof64_s(strs[1], &phong[PHONG_KA]) == ERROR
		|| ft_atof64_s(strs[2], &phong[PHONG_KD]) == ERROR
		|| ft_atof64_s(strs[3], &phong[PHONG_KS]) == ERROR)
		return (ERROR);
	phong[PHONG_SHINI] = (t_f64)shini;
	object_set_phong(obj, phong);
	return (SUCCESS);
}
