/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:33:24 by vparis            #+#    #+#             */
/*   Updated: 2018/03/24 23:02:17 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "matrix.h"
#include "objects.h"
#include "rtv1.h"

inline int		is_light(t_object *obj)
{
	return (obj->type == LIGHT);
}

t_obj_lst		*find_next_light(t_obj_lst *lst)
{
	while (lst != NULL && !is_light(lst->object))
		lst = lst->next;
	return (lst);
}

t_obj_lst		*find_next_object(t_obj_lst *lst)
{
	while (lst != NULL && is_light(lst->object))
		lst = lst->next;
	return (lst);
}

int				is_shadow(t_env *env, t_ray *ray_light, t_solution *solution)
{
	t_obj_lst	*iter_object;

	iter_object = env->objects;
	while ((iter_object = find_next_object(iter_object)) != NULL)
	{
		if (env->intersect[iter_object->object->type](ray_light,
			iter_object->object, solution) == SUCCESS)
			if (solution->t0 < solution->t && solution->t0 > 0.)
				return (SUCCESS);
		iter_object = iter_object->next;
	}
	return (ERROR);
}

t_f64			compute_raylight(t_ray *ray, t_ray *ray_hit, t_ray *ray_light,
									t_object *obj)
{
	t_f64	r;

	vec3_cpy(&(ray_light->orig), &(obj->pos));
	vec3_sub(&(ray_light->orig), &(ray_hit->orig));
	r = vec3_len(&(ray_light->orig));
	vec3_cpy(&(ray_light->dir), &(ray_light->orig));
	vec3_norm(&(ray_light->dir));
	vec3_cpy(&(ray_light->orig), &(ray->orig));
	return (r);
}
