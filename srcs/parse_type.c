/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:09:01 by vparis            #+#    #+#             */
/*   Updated: 2018/03/22 17:08:28 by vparis           ###   ########.fr       */
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

t_parse_type	*get_parse_funs(void)
{
	static t_parse_type	parse_type[] = {
		{"width", &parse_t_width, "0", 1},
		{"height", &parse_t_height, "0", 1},
		{"background", &parse_t_background, "0", 3},
		{"ang", &parse_t_ang, "1", 3},
		{"orig", &parse_t_orig, "1", 3},
		{"fov", &parse_t_fov, "1", 1},
		{"pos", &parse_t_pos, "23456", 3},
		{"dir", &parse_t_dir, "3456", 3},
		{"size", &parse_t_size, "3456", 1},
		{"color", &parse_t_color, "23456", 3},
		{"intensity", &parse_t_intensity, "2", 3},
		{"phong", &parse_t_phong, "3456", 4},
		{NULL, NULL, NULL, 0}
	};

	return (parse_type);
}

size_t			ft_strcountc(char *str, char c)
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

char			**get_line(char *str)
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

int				check_line_object(char *lst, int type)
{
	if (ft_strchr(lst, '0' + type) != NULL)
		return (SUCCESS);
	return (ERROR);
}

int				check_line_type(char **line, t_parse_type *data, int type)
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

int		check_counter_details(int counter[OBJECT_DETAILS_SIZE], int type)
{
	if (type == 0)
		return (counter[0] == 1 && counter[1] == 1 && counter[2] == 1);
	else if (type == 1)
		return (counter[3] == 1 && counter[4] == 1 && counter[5] == 1);
	else if (type == 2)
		return (counter[6] == 1 && counter[9] == 1  && counter[10] == 1);
	else
		return (counter[6] == 1 && counter[7] == 1 && counter[8] == 1
			&& counter[9] == 1 && counter[11] == 1);
	return (0);
}

int				parse_global(t_env *env, char **str, int type)
{
	int				i;
	int				r;
	char			**tmp;
	int				counter[OBJECT_DETAILS_SIZE];

	ft_bzero(counter, OBJECT_DETAILS_SIZE * sizeof(int));
	i = 0;
	while (*(str + i) != NULL)
	{
		if ((tmp = check_line(*(str + i), type, &r)) == NULL)
			break ;
		if (counter[r] == 1 || parse_details(env, r, tmp[1]) == ERROR)
		{
			ft_strsplit_free(tmp);
			return (-1);
		}
		counter[r] += 1;
		ft_strsplit_free(tmp);
		i++;
	}
	if (!check_counter_details(counter, type))
		return (-1);
	return (i);
}
