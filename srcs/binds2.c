/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:26:03 by vparis            #+#    #+#             */
/*   Updated: 2018/02/26 11:19:55 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"
#include "rtv1.h"

void		check_key2(t_env *env)
{
	env->refresh = (env->refresh == 2) ? 1 : 0;
}

void		check_key(t_env *env)
{
	env->refresh += 1;
	check_key2(env);
}
