/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:46:39 by vparis            #+#    #+#             */
/*   Updated: 2018/03/08 14:16:55 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_mlx.h"
#include "objects.h"
#include "matrix.h"

t_object	*object_new(int type, t_vec3 *pos, t_vec3 *dir,
			t_f64 radius, t_vec3 *color, t_vec3 *e_color)
{
	t_object	*tmp;

	if ((tmp = (t_object *)malloc(sizeof(t_object))) == NULL)
		return (NULL);
	tmp->type = type;
	tmp->radius = radius;
	tmp->radius2 = radius * radius;
	vec3_cpy(&(tmp->color), color);
	vec3_cpy(&(tmp->e_color), e_color);
	vec3_cpy(&(tmp->pos), pos);
	vec3_norm(dir);
	vec3_cpy(&(tmp->norm), dir);
	return (tmp);
}

t_obj_lst	*object_add(t_obj_lst **objects, t_object *object)
{
	t_obj_lst	*tmp;

	if ((tmp = (t_obj_lst *)malloc(sizeof(t_obj_lst))) == NULL)
		return (NULL);
	tmp->object = object;
	tmp->next = *objects;
	*objects = tmp;
	return (*objects);
}

void		object_free(t_obj_lst **objects)
{
	t_obj_lst	*iter;
	t_obj_lst	*tmp;

	iter = *objects;
	while (iter != NULL)
	{
		tmp = iter->next;
		free(iter);
		iter = tmp;
	}
	*objects = NULL;
}
