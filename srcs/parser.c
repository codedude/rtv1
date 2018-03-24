/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:31:17 by valentin          #+#    #+#             */
/*   Updated: 2018/03/24 18:11:39 by valentin         ###   ########.fr       */
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

int		parse_check_header(char *str)
{
	if (ft_strcmp(str, "plane") == 0)
		return (0);
	else if (ft_strcmp(str, "sphere") == 0)
		return (1);
	else if (ft_strcmp(str, "cone") == 0)
		return (2);
	else if (ft_strcmp(str, "cylinder") == 0)
		return (3);
	else if (ft_strcmp(str, "light") == 0)
		return (4);
	else if (ft_strcmp(str, "canvas") == 0)
		return (5);
	else if (ft_strcmp(str, "camera") == 0)
		return (6);
	else
		return (-1);
}

int		check_counter(int counter[OBJECT_SIZE])
{
	return (counter[5] == 1 && counter[6] == 1);
}

/*
** Keep print for DEBUG
*/

int		parse_data(t_env *env, char **data)
{
	int		i;
	int		type;
	int		r;
	int		counter[OBJECT_SIZE];

	i = 0;
	ft_bzero(counter, OBJECT_SIZE * sizeof(int));
	while (data[i] != NULL)
	{
		r = ERROR;
		if ((type = parse_check_header(data[i])) == -1)
		{
			ft_putendl("type\n");
			break ;
		}
		counter[type] += 1;
		i++;
		if (data[i] != NULL && (data[i][0] != T_OPEN || data[i][1] != 0))
		{
			ft_putendl("open\n");
			break ;
		}
		i++;
		if ((type = parse_global(env, &data[i], type)) > 0)
		{
			i += type;
			if (data[i] != NULL && (data[i][0] != T_CLOSE || data[i][1] != 0))
			{
				ft_putendl("close\n");
				break ;
			}
		}
		else
		{
			ft_putendl("data\n");
			break ;
		}
		i++;
		r = SUCCESS;
	}
	if (!check_counter(counter))
		r = ERROR;
	return (r);
}

int		parse_map(t_env *env, char *map)
{
	char	*map_str;
	char	**map_cut;

	if (check_map(map) == ERROR)
	{
		ft_putendl("Invalid file");
		return (ERROR);
	}
	if ((map_str = read_map(map)) == NULL)
		return (ERROR);
	map_cut = cut_map(map_str);
	free(map_str);
	if (map_cut == NULL)
		return (ERROR);
	if (parse_data(env, map_cut) == ERROR)
	{
		ft_putendl("Invalid file");
		return (ERROR);
	}
	return (SUCCESS);
}
