/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_details.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:59:53 by vparis            #+#    #+#             */
/*   Updated: 2018/03/24 22:24:20 by valentin         ###   ########.fr       */
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

int		check_numbers(char **tmp)
{
	int		i;
	int		j;
	int		sign;

	i = 0;
	while (tmp[i] != NULL)
	{
		j = 0;
		sign = 0;
		if (tmp[i][j] == '+' || tmp[i][j] == '-')
			sign = ++j > 0;
		while (ft_isdigit(tmp[i][j]))
			j++;
		if (tmp[i][j] == 0 && j > sign)
			return (SUCCESS);
		if(tmp[i][j] == '.' && j > sign)
			j++;
		while (ft_isdigit(tmp[i][j]))
			j++;
		if (tmp[i][j] != 0 || j < 3 + sign)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static size_t	len_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	return (i);
}

int		parse_details(t_env *env, int id, char *line, t_object *obj)
{
	t_parse_type	*parse_funs;
	char			**tmp;
	int				r;
	void			*param;

	r = SUCCESS;
	if ((tmp = ft_strsplit_whitespaces(line)) == NULL)
		return (ERROR);
	parse_funs = get_parse_funs();

	if (parse_funs[id].size != len_strs(tmp) || check_numbers(tmp) == ERROR)
		r = ERROR;
	if (obj == NULL)
		param = (void *)env;
	else
		param = (void *)obj;
	if ((*parse_funs[id].f)(param, tmp) == ERROR)
		r = ERROR;
	ft_strsplit_free(tmp);
	return (r);
}
