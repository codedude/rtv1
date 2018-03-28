/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:09:01 by vparis            #+#    #+#             */
/*   Updated: 2018/03/28 14:03:34 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "rtv1.h"
#include "matrix.h"
#include "objects.h"

static size_t	ft_strcountc(char *str, char c)
{
	size_t	i;
	size_t	r;

	i = 0;
	r = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			r++;
		i++;
	}
	return (r);
}

static char		**get_line(char *str)
{
	char	**tmp;
	int		i;

	if (ft_strcountc(str, T_SEPAR) != 1)
		return (NULL);
	if ((tmp = ft_strsplit(str, T_SEPAR)) == NULL)
		return (NULL);
	if (tmp[0] == NULL || tmp[1] == NULL || tmp[2] != NULL)
	{
		ft_strsplit_free(tmp);
		return (NULL);
	}
	i = 0;
	while (tmp[i] != NULL)
	{
		if (trim_content(&tmp[i]) == ERROR)
		{
			ft_strsplit_free(tmp);
			return (NULL);
		}
		i++;
	}
	return (tmp);
}

static int		check_line_object(char *lst, int type)
{
	if (ft_strchr(lst, '0' + type) != NULL)
		return (SUCCESS);
	return (ERROR);
}

static int		check_line_type(char **line, t_parse_type *data, int type)
{
	if (check_line_object(data->types, type) == ERROR)
		return (ERROR);
	if (ft_strcmp(line[0], data->name) != 0)
		return (ERROR);
	return (SUCCESS);
}

char			**check_line(char *str, int type, int *r)
{
	char			**tmp;
	t_parse_type	*parse_funs;
	int				i;

	if ((tmp = get_line(str)) == NULL)
		return (NULL);
	parse_funs = get_parse_funs();
	i = 0;
	while (parse_funs[i].name != NULL)
	{
		if (check_line_type(tmp, &(parse_funs[i]), type) == SUCCESS)
		{
			*r = i;
			break ;
		}
		i++;
	}
	if (parse_funs[i].name == NULL)
	{
		ft_strsplit_free(tmp);
		tmp = NULL;
	}
	return (tmp);
}
