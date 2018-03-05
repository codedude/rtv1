/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 11:01:14 by vparis            #+#    #+#             */
/*   Updated: 2018/03/05 11:02:54 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_mlx.h"
#include "rtv1.h"

static void	get_filename(int nb, char *filename)
{
	ft_bzero(filename, 20);
	ft_strcpy(filename, FILE_NAME);
	filename[13] = '0' + nb / 100;
	filename[14] = '0' + nb / 10 - (nb / 100) * 10;
	filename[15] = '0' + nb % 10;
}

int			write_header(int fd, int size[2])
{
	write(fd, "BM", 2);
	write_int(fd, (size[0] * size[1] * sizeof(t_color) + 54), 4);
	write_int(fd, 0x00, 4);
	write_int(fd, 0x36, 4);
	return (SUCCESS);
}

int			write_dibheader(int fd, int size[2])
{
	write_int(fd, 0x28, 4);
	write_int(fd, size[1], 4);
	write_int(fd, size[0], 4);
	write_int(fd, 0x01, 2);
	write_int(fd, 0x20, 2);
	write_int(fd, 0x00, 4);
	write_int(fd, 0x00, 4);
	write_int(fd, 0x0B13, 4);
	write_int(fd, 0x0B13, 4);
	write_int(fd, 0x00, 4);
	write_int(fd, 0x00, 4);
	return (SUCCESS);
}

int			save_img(t_data *data)
{
	int			size[2];
	t_color		*img;
	char		filename[26];
	int			fd;
	static int	nb = 0;

	if (data->env.save_img == 0)
		return (SUCCESS);
	data->env.save_img = 0;
	size[0] = data->mlx.win[MAIN_WIN].height;
	size[1] = data->mlx.win[MAIN_WIN].width;
	img = data->mlx.win[MAIN_WIN].img;
	get_filename(nb, filename);
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
		return (ERROR);
	ft_putstr("Saving image... ");
	write_header(fd, size);
	write_dibheader(fd, size);
	write_img(fd, size, img);
	close(fd);
	nb++;
	ft_putstr("Image saved in ");
	ft_putendl(filename);
	return (SUCCESS);
}
