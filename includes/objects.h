/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:32:54 by vparis            #+#    #+#             */
/*   Updated: 2018/03/24 18:03:48 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "libft.h"
# include "ft_mlx.h"
# include "matrix.h"

# define OBJECTS		4
# define PLANE			0
# define SPHERE			1
# define CONE			2
# define CYLINDER		3
# define LIGHT			4

# define PHONGS			4
# define PHONG_SHINI	0
# define PHONG_KA		1
# define PHONG_KD		2
# define PHONG_KS		3

typedef struct			s_object {
	t_vec3				pos;
	t_vec3				norm;
	t_vec3				color;
	t_vec3				intensity;
	t_f64				radius;
	t_f64				radius2;
	t_f64				phong[PHONGS];
	int					type;
}						t_object;

typedef struct			s_obj_lst {
	struct s_obj_lst	*next;
	t_object			*object;
}						t_obj_lst;

t_object				*object_new(int type);
t_obj_lst				*object_add(t_obj_lst **objects, t_object *object);
void					object_free(t_obj_lst **objects);

void					object_set_pos(t_object *obj, t_vec3 *pos);
void					object_set_dir(t_object *obj, t_vec3 *dir);
void					object_set_intensity(t_object *obj, t_vec3 *intensity);
void					object_set_color(t_object *obj, t_vec3 *color);
void					object_set_radius(t_object *obj, t_f64 radius);
void					object_set_phong(t_object *obj, t_f64 phong[PHONGS]);

#endif
