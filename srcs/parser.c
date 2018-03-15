/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:31:17 by valentin          #+#    #+#             */
/*   Updated: 2018/03/15 11:51:42 by valentin         ###   ########.fr       */
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

int		parse_map(t_env *env, char *map)
{
	char	*map_str;
	char	**map_cut;
	int		i;

	if ((map_str = read_map(map)) == NULL)
		return (ERROR);
	map_cut = cut_map(map_str);
	free(map_str);
	if (map_cut == NULL)
		return (ERROR);
	i = 0;
	while (map_cut[i] != NULL)
	{
		printf("$%s$\n", map_cut[i]);
		i++;
	}
	return (SUCCESS);
}
