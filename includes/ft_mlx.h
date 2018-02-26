/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:44:18 by vparis            #+#    #+#             */
/*   Updated: 2018/02/08 13:37:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include "libft.h"
# include "ft_tpool.h"
# include "mlx.h"
# include "ft_mlx_key.h"

# define MLX_MAX_WINDOW	4
# define MAIN_WIN		0

# define C_RED			0x00FF0000
# define C_GREEN		0x0000FF00
# define C_BLUE			0x000000FF
# define C_WHITE		0x00FFFFFF
# define C_BLACK		0x00000000
# define C_GREY			0x00999999

# define BMP_BUFF		1024

typedef int		t_color;

typedef struct	s_win {
	void		*win;
	t_color		*img;
	void		*img__;
	int			width;
	int			height;
	char		*title;
}				t_win;

typedef struct	s_mlx {
	void		*mlx;
	t_win		win[MLX_MAX_WINDOW];
}				t_mlx;

/*
** MLX and window management
*/

void			ft_mlx_init(t_mlx *mlx);
int				ft_mlx_win(t_mlx *mlx, int width, int height, char *title);
void			ft_mlx_destroy(t_mlx *mlx, int win);
int				ft_mlx_exit(void);
void			ft_mlx_fps(int show_fps, int refresh);

/*
** Pixel manipulation
*/

t_color			ft_mlx_getcolor(int r, int g, int b);

#endif
