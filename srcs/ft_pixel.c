/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:48:34 by vparis            #+#    #+#             */
/*   Updated: 2018/02/26 15:54:52 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

t_color	ft_mlx_getcolor(int r, int g, int b)
{
	t_color		c;

	c = 0;
	c |= (b & 0xFF);
	c |= (g & 0xFF) << 8;
	c |= (r & 0xFF) << 16;
	return (c);
}

void	ft_mlx_put(t_mlx *mlx, int x, int y, t_color c)
{
	mlx->win[MAIN_WIN].img[y * mlx->win[MAIN_WIN].width + x] = c;
}
