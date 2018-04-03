/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:46:39 by vparis            #+#    #+#             */
/*   Updated: 2018/04/03 14:35:15 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_mlx.h"
#include "objects.h"
#include "matrix.h"

void		object_set_pos(t_object *obj, t_vec3 *pos)
{
	vec3_cpy(&(obj->pos), pos);
}

void		object_set_dir(t_object *obj, t_vec3 *dir)
{
	vec3_cpy(&(obj->norm), dir);
	vec3_norm(&(obj->norm));
}

t_object	*object_new(int type)
{
	t_object	*tmp;

	if ((tmp = (t_object *)malloc(sizeof(t_object))) == NULL)
		return (NULL);
	ft_bzero(tmp, sizeof(t_object));
	tmp->type = type;
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
