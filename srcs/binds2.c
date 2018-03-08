/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:26:03 by vparis            #+#    #+#             */
/*   Updated: 2018/03/08 15:02:05 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"
#include "rtv1.h"

void		check_key2(t_env *env)
{
	if (env->keydown == K_Q)
		env->cam_ang.x += MOVE_DELTA;
	else if (env->keydown == K_A)
		env->cam_ang.x -= MOVE_DELTA;
	else if (env->keydown == K_W)
		env->cam_ang.y += MOVE_DELTA;
	else if (env->keydown == K_S)
		env->cam_ang.y -= MOVE_DELTA;
	else if (env->keydown == K_E)
		env->cam_ang.z += MOVE_DELTA;
	else if (env->keydown == K_D)
		env->cam_ang.z -= MOVE_DELTA;
	else
		env->refresh = (env->refresh == 2) ? 1 : 0;
}

void		check_key(t_env *env)
{
	env->refresh += 1;
	if (env->keydown == K_UP)
		env->cam_orig.y += MOVE_DELTA;
	else if (env->keydown == K_DOWN)
		env->cam_orig.y -= MOVE_DELTA;
	else if (env->keydown == K_LEFT)
		env->cam_orig.x -= MOVE_DELTA;
	else if (env->keydown == K_RIGHT)
		env->cam_orig.x += MOVE_DELTA;
	else if (env->keydown == K_Z)
		env->cam_orig.z += MOVE_DELTA;
	else if (env->keydown == K_X)
		env->cam_orig.z -= MOVE_DELTA;
	else
		check_key2(env);
}
