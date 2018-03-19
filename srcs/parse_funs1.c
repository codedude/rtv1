/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:30:20 by vparis            #+#    #+#             */
/*   Updated: 2018/03/19 20:42:19 by vparis           ###   ########.fr       */
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

static int	check_str(const char *str, int *id)
{
	int sign;
	int i;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	else if (!ft_isdigit(str[i]))
		sign = 0;
	*id = i;
	return (sign);
}

int			sft_atoi(const char *nptr)
{
	int i;
	int n;
	int sign;

	i = 0;
	n = 0;
	sign = check_str(nptr, &i);
	if (sign == 0)
		return (n);
	while (ft_isdigit(nptr[i]))
		n = n * 10 + nptr[i++] - '0';
	return (n * sign);
}

int		parse_t_width(t_env *env, char *str)
{
	int		n;

	n = sft_atoi(str);
	env->width = n;
	return (SUCCESS);
}

int		parse_t_height(t_env *env, char *str)
{
	int		n;

	n = sft_atoi(str);
	env->height = n;
	return (SUCCESS);
}

int		parse_t_background(t_env *env, char *str)
{

	return (SUCCESS);
}

int		parse_t_ang(t_env *env, char *str)
{

	return (SUCCESS);
}

int		parse_t_fov(t_env *env, char *str)
{

	return (SUCCESS);
}
