/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:31:22 by valentin          #+#    #+#             */
/*   Updated: 2018/03/15 11:51:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "parser.h"

char		*read_map(char *filename)
{
	int		r;
	int		fd;
	int		n;
	int		read_size;
	char	*buff;

	if (filename == NULL)
		return (NULL);
	if ((fd = open(filename, O_RDONLY | O_NONBLOCK | O_NOFOLLOW)) < 0)
	{
		ft_putendl("Invalid path");
		return (NULL);
	}
	if ((buff = (char *)malloc(BUFF_SIZE + 1)) == NULL)
	{
		close(fd);
		return (NULL);
	}
	n = 0;
	read_size = BUFF_READ;
	while ((r = read(fd, &buff[n], read_size)) > 0)
	{
		n += r;
		if (n + read_size > BUFF_SIZE - 1)
		{
			if ((read_size = BUFF_SIZE - 1 - n) < 1)
			{
				free(buff);
				close(fd);
				ft_putendl("File too big");
				return (NULL);
			}
		}
	}
	buff[n] = 0;
	close(fd);
	return (buff);
}

static int	trim_content(char **dest)
{
	char	*tmp;

	if ((tmp = ft_strtrim(*dest)) == NULL)
		return (ERROR);
	free(*dest);
	*dest = tmp;
	return (SUCCESS);
}

char		**cut_map(char *map)
{
	char	**tmp;
	int		i;
	int		j;

	if ((tmp = ft_strsplit_str(map, "\n")) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (tmp[i] != NULL)
	{
		if (trim_content(&tmp[i]) == ERROR)
		{
			ft_strsplit_free(tmp);
			return (NULL);
		}
		if (tmp[i][0] == T_COMMENT || tmp[i][0] == 0)
			free(tmp[i]);
		else
		{
			if (j != i)
				tmp[j] = tmp[i];
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}
