/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:47:10 by vparis            #+#    #+#             */
/*   Updated: 2018/04/03 14:30:17 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			clean_maps(t_data *data)
{
	t_color	*tmp;
	int		i;

	tmp = data->mlx.win[MAIN_WIN].img;
	i = 0;
	while (i < data->env.height * data->env.width)
	{
		tmp[i] = data->env.background;
		i++;
	}
}

void			draw_img(t_data *data)
{
	t_algo		pack[TASKS];
	int			n_div;
	int			n_mod;
	int			i;
	int			tasks;

	i = 0;
	tasks = TASKS;
	n_div = data->env.height / tasks;
	n_mod = data->env.height % tasks;
	while (i < tasks)
	{
		pack[i].data = data;
		pack[i].start = i * n_div;
		pack[i].end = i < tasks - 1 ? n_div : n_div + n_mod;
		pack[i].end += pack[i].start;
		tp_add_task(data->env.tp, &draw_rt, &pack[i]);
		i++;
	}
	data->env.rot = matrix_rot(&(data->env.cam_ang));
	tp_wait_for_queue(data->env.tp);
	matrix_del(MATRIX_33, &(data->env.rot));
}
