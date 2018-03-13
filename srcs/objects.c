/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:46:39 by vparis            #+#    #+#             */
/*   Updated: 2018/03/13 16:29:07 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "ft_mlx.h"
#include "objects.h"
#include "matrix.h"

t_f64		clamp_f64(t_f64 f, t_f64 lmin, t_f64 lmax)
{
	if (f < lmin)
		return (lmin);
	else if (f > lmax)
		return (lmax);
	return (f);
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
