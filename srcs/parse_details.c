/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_details.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:59:53 by vparis            #+#    #+#             */
/*   Updated: 2018/03/20 17:42:08 by vparis           ###   ########.fr       */
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
		if(tmp[i][j] == '.')
			j++;
		while (ft_isdigit(tmp[i][j]))
			j++;
		if (tmp[i][j] != 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int		parse_details(t_env *env, int id, char *line)
{
	t_parse_type	*parse_funs;
	char			**tmp;
	int				r;

	r = SUCCESS;
	if ((tmp = ft_strsplit_whitespaces(line)) == NULL)
		return (ERROR);
	parse_funs = get_parse_funs();
	if (check_numbers(tmp) == ERROR
		|| (*parse_funs[id].f)(env, tmp) == ERROR)
		r = ERROR;
	ft_strsplit_free(tmp);
	return (r);
}
