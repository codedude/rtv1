/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:32:54 by vparis            #+#    #+#             */
/*   Updated: 2018/03/09 17:26:28 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "libft.h"
# include "ft_mlx.h"
# include "matrix.h"

# define KS		0.15
# define KD		0.90
# define KA		0.1
# define KDIST	1.0

# define LIGHT	0
# define PLANE	1
# define SPHERE	2
# define CONE	3
# define CYLIND	4

typedef struct			s_object {
	t_vec3				pos;
	t_vec3				norm;
	t_vec3				color;
	t_vec3				intensity;
	t_f64				radius;
	t_f64				radius2;
	t_f64				shini;
	int					type;
}						t_object;

typedef struct			s_obj_lst {
	struct s_obj_lst	*next;
	t_object			*object;
}						t_obj_lst;

t_object	*object_new(int type, t_vec3 *pos, t_vec3 *dir,
			t_f64 radius, t_vec3 *color, t_f64 shini, t_vec3 *intensity);
t_obj_lst	*object_add(t_obj_lst **objects, t_object *object);
void		object_free(t_obj_lst **objects);

#endif
