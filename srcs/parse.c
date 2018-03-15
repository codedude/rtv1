/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:28:53 by vparis            #+#    #+#             */
/*   Updated: 2018/03/15 14:18:36 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "ft_mlx.h"
#include "objects.h"
#include "matrix.h"
#include "rtv1.h"

void		env_init_scene(t_env *env)
{
	t_object	*objs[50];
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		color;
	t_vec3		intens_d;
	t_f64		phong[PHONGS];

	phong[PHONG_KA] = 0.1;

	
	vec3_set(&intens_d, 0.0, 0.0, 0.0);
	phong[PHONG_SHINI] = 0.0; phong[PHONG_KD] = 1.0; phong[PHONG_KS] = 0.0;
//PLANE
	vec3_set(&pos, 0., 0., 0.);
	vec3_set(&dir, 0.0, 1.0, 0.0);
	vec3_set(&color, .98, 0.95, 0.80);
	objs[35] = object_new(PLANE, &pos, &dir, 1., &color, phong, &intens_d);

	vec3_set(&pos, 0., 0., -250.);
	vec3_set(&dir, 0.0, 0.0, 1.0);
	objs[36] = object_new(PLANE, &pos, &dir, 1., &color, phong, &intens_d);

	vec3_set(&pos, 50., 0., 0.);
	vec3_set(&dir, -1.0, 0.0, 0.0);
	objs[37] = object_new(PLANE, &pos, &dir, 1., &color, phong, &intens_d);

	vec3_set(&pos, -50., 0., 0.);
	vec3_set(&dir, 1.0, 0.0, 0.0);
	objs[38] = object_new(PLANE, &pos, &dir, 1., &color, phong, &intens_d);

	phong[PHONG_SHINI] = 12.0; phong[PHONG_KD] = 0.85; phong[PHONG_KS] = 0.4;
//CYLINDER
	vec3_set(&pos, -30, 0.0, -21.0);
	vec3_set(&dir, 0.0, 1.0, 0.0);
	vec3_set(&color, 0.50, 0.80, 0.90);
	objs[10] = object_new(CYLINDER, &pos, &dir, 3., &color, phong, &intens_d);

	vec3_set(&pos, 30, 0.0, -21.0);
	vec3_set(&dir, 0.0, 1.0, 0.0);
	vec3_set(&color, 0.50, 0.80, 0.90);
	objs[11] = object_new(CYLINDER, &pos, &dir, 3., &color, phong, &intens_d);

	vec3_set(&pos, 0.0, 10.0, -80.0);
	vec3_set(&dir, 1.0, 0.0, 0.0);
	vec3_set(&color, 0.90, 0.50, 0.80);
	objs[12] = object_new(CYLINDER, &pos, &dir, 5., &color, phong, &intens_d);

//CONE
	vec3_set(&pos, -50, 15, -10);
	vec3_set(&dir, 0.2, -0.2, -0.02);
	vec3_set(&color, 0.80, 0.50, 0.90);
	objs[14] = object_new(CONE, &pos, &dir, 10., &color, phong, &intens_d);

	vec3_set(&pos, 50, 5, -10);
	vec3_set(&dir, -0.2, -0.2, 0.02);
	vec3_set(&color, 0.80, 0.50, 0.90);
	objs[15] = object_new(CONE, &pos, &dir, 20., &color, phong, &intens_d);

	vec3_set(&dir, 0., 0., 0.);
	vec3_set(&color, 1.0, 1.0, 1.0);

	phong[PHONG_SHINI] = 0.0; phong[PHONG_KD] = 1.0; phong[PHONG_KS] = 0.0;
//LIGHT
	vec3_set(&pos, 0.0, 80.0, 0.0);
	vec3_set(&intens_d, 0.6, 0.6, 0.6);
	objs[30] = object_new(LIGHT, &pos, &dir, 1., &color, phong, &intens_d);

	vec3_set(&pos, -80.0, 2.0, 30.0);
	vec3_set(&intens_d, 1.0, 1.0, 1.0);
	objs[31] = object_new(LIGHT, &pos, &dir, 1., &color, phong, &intens_d);

	vec3_set(&pos, 80.0, 2.0, 30.0);
	vec3_set(&intens_d, 1.0, 1.0, 1.0);
	objs[32] = object_new(LIGHT, &pos, &dir, 1., &color, phong, &intens_d);

	vec3_set(&pos, -100.0, 8.0, 80.0);
	vec3_set(&intens_d, 3., 3., 3.);
	objs[33] = object_new(LIGHT, &pos, &dir, 1., &color, phong, &intens_d);

	vec3_set(&intens_d, 0.0, 0.0, 0.0);

	phong[PHONG_KD] = 0.90; phong[PHONG_KS] = 0.33;
//SPHERES
	vec3_set(&pos, 0.0, -76., 0.);
	vec3_set(&color, 0.70, 0.70, 0.70);
	phong[PHONG_SHINI] = 4.0;
	objs[3] = object_new(SPHERE, &pos, &dir, 80., &color, phong, &intens_d);

	vec3_set(&pos, 0.0, 12.5, 0.0);
	vec3_set(&color, 1.00, 0.32, 0.36);
	phong[PHONG_SHINI] = 10.0;
	objs[4] = object_new(SPHERE, &pos, &dir, 5., &color, phong, &intens_d);

	vec3_set(&pos, -10.0, 21.0, 10.0);
	vec3_set(&color, 0.50, 0.90, 0.50);
	phong[PHONG_SHINI] = 0.0;
	objs[5] = object_new(SPHERE, &pos, &dir, 3., &color, phong, &intens_d);

	vec3_set(&pos, 13, 30.0, -100.0);
	vec3_set(&color, 0.65, 0.77, 0.97);
	phong[PHONG_SHINI] = 40.0;
	phong[PHONG_KS] = 1.0;
	objs[6] = object_new(SPHERE, &pos, &dir, 40., &color, phong, &intens_d);

	phong[PHONG_SHINI] = 5.0;
	phong[PHONG_KS] = 0.33;
	vec3_set(&pos, -15.0, 10, -10);
	vec3_set(&color, 0.90, 0.76, 0.46);
	objs[7] = object_new(SPHERE, &pos, &dir, 2., &color, phong, &intens_d);
	vec3_set(&pos, 15.0, 18, -10);
	vec3_set(&color, 0.90, 0.76, 0.46);
	objs[8] = object_new(SPHERE, &pos, &dir, 2., &color, phong, &intens_d);
	vec3_set(&pos, 21.0, 18, -10);
	vec3_set(&color, 0.90, 0.76, 0.46);
	objs[9] = object_new(SPHERE, &pos, &dir, 2., &color, phong, &intens_d);

//PLANE
	object_add(&(env->objects), objs[35]);
	object_add(&(env->objects), objs[36]);
	//object_add(&(env->objects), objs[37]);
	//object_add(&(env->objects), objs[38]);
//LIGHT
	object_add(&(env->objects), objs[30]);
	object_add(&(env->objects), objs[31]);
	object_add(&(env->objects), objs[32]);
	//object_add(&(env->objects), objs[33]);
//SPHERE
	object_add(&(env->objects), objs[3]);
	object_add(&(env->objects), objs[4]);
	object_add(&(env->objects), objs[5]);
	object_add(&(env->objects), objs[6]);
	//object_add(&(env->objects), objs[7]);
	//object_add(&(env->objects), objs[8]);
	//object_add(&(env->objects), objs[9]);
//CYLINDER
	object_add(&(env->objects), objs[10]);
	object_add(&(env->objects), objs[11]);
	//object_add(&(env->objects), objs[12]);
	//object_add(&(env->objects), objs[13]);
//CONE
	object_add(&(env->objects), objs[14]);
	object_add(&(env->objects), objs[15]);
	//object_add(&(env->objects), objs[16]);
	//object_add(&(env->objects), objs[17]);
}

t_object	*object_new(int type, t_vec3 *pos, t_vec3 *dir,
			t_f64 radius, t_vec3 *color, t_f64 phong[PHONGS], t_vec3 *intensity)
{
	t_object	*tmp;

	if ((tmp = (t_object *)malloc(sizeof(t_object))) == NULL)
		return (NULL);
	tmp->type = type;
	tmp->phong[PHONG_SHINI] = round(clamp_f64(phong[PHONG_SHINI], 0.0, 1200.0));
	tmp->phong[PHONG_KA] = clamp_f64(phong[PHONG_KA], 0.0, 1.0);
	tmp->phong[PHONG_KD] = clamp_f64(phong[PHONG_KD], 0.0, 1.0);
	tmp->phong[PHONG_KS] = clamp_f64(phong[PHONG_KS], 0.0, 1.0);
	tmp->radius = clamp_f64(radius, 0.001, 1000.0);
	tmp->radius2 = radius * radius;
	vec3_cpy(&(tmp->color), color);
	vec3_cpy(&(tmp->intensity), intensity);
	vec3_cpy(&(tmp->pos), pos);
	vec3_norm(dir);
	vec3_cpy(&(tmp->norm), dir);
	return (tmp);
}