/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_pool2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 22:46:27 by valentin          #+#    #+#             */
/*   Updated: 2018/03/26 20:12:46 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_tpool.h"

static int	tp_find_slot(t_tpool *tp)
{
	int	i;

	i = 0;
	while (i < tp->size)
	{
		if (tp->threads[i].state == TH_READY)
			return (i);
		i++;
	}
	return (-1);
}

static int	tp_is_done(t_tpool *tp)
{
	int	i;

	i = 0;
	while (i < tp->size)
	{
		if (tp->threads[i].state == TH_BUSY)
			return (0);
		i++;
	}
	return (1);
}

static int	tp_is_queue(t_tpool *tp)
{
	return (tp->queue->size > 0);
}

static int	tp_launch_task(t_tpool *tp)
{
	int			i;
	t_tp_data	*tp_data;

	while ((i = tp_find_slot(tp)) != -1)
	{
		if (tp->threads[i].thread == 0 && (tp->flag & TP_MASK_ON) == TP_ON_EXEC)
		{
			if (th_start(tp, i, &th_fun_start) == ERROR)
				return (ERROR);
		}
		if ((tp_data = (t_tp_data *)tp_queue_shift(tp->queue)) == NULL)
			break ;
		tp->threads[i].data = tp_data;
		pthread_mutex_lock(&(tp->threads[i].mutex));
		tp->threads[i].state = TH_BUSY;
		pthread_cond_signal(&(tp->threads[i].cond));
		pthread_mutex_unlock(&(tp->threads[i].mutex));
	}
	return (SUCCESS);
}

int			tp_wait_for_queue(t_tpool *tp)
{
	tp->working_threads = 0;
	tp_launch_task(tp);
	pthread_mutex_lock(&(tp->mutex));
	while (tp_is_queue(tp) || tp_is_done(tp) == 0)
	{
		pthread_cond_wait(&(tp->cond), &(tp->mutex));
		if (tp_launch_task(tp) == ERROR)
		{
			pthread_mutex_unlock(&(tp->mutex));
			return (ERROR);
		}
	}
	pthread_mutex_unlock(&(tp->mutex));
	return (SUCCESS);
}
