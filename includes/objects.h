/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:32:54 by vparis            #+#    #+#             */
/*   Updated: 2018/02/26 18:20:21 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "libft.h"
# include "ft_mlx.h"
# include "matrix.h"

# define LIGHT	0
# define PLAN	1
# define SPHERE	2

typedef struct			s_object {
	t_vec3				pos;
	t_vec3				color;
	t_vec3				e_color;
	t_f64				radius;
	t_f64				radius2;
	t_f64				transparency;
	t_f64				reflection;
	int					type;
}						t_object;

typedef struct			s_obj_lst {
	struct s_obj_lst	*next;
	t_object			*object;
}						t_obj_lst;

t_object	*object_new(int type, t_vec3 *pos, t_f64 radius, t_vec3 *color, 
						t_vec3 *e_color, t_f64 t, t_f64 r);
t_obj_lst	*object_add(t_obj_lst **objects, t_object *object);
void		object_free(t_obj_lst **objects);

#endif
