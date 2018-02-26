/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:02:38 by vparis            #+#    #+#             */
/*   Updated: 2018/01/08 13:57:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "matrix.h"

t_matrix	matrix_new(int type, int init)
{
	int			l;
	int			c;
	int			i;
	t_matrix	tmp;

	matrix_getsize(type, &l, &c);
	if ((tmp = (t_matrix)malloc(sizeof(*tmp) * l)) == NULL)
		return (NULL);
	i = 0;
	while (i < l)
	{
		if ((tmp[i] = (MATRIX_T *)malloc(sizeof(tmp[i]) * c)) == NULL)
			return (NULL);
		if (init != 0)
			ft_bzero((void *)tmp[i], sizeof(MATRIX_T) * c);
		i++;
	}
	return (tmp);
}

void		matrix_del(int type, t_matrix *mat)
{
	int			l;
	int			c;

	matrix_getsize(type, &l, &c);
	while (l != 0)
	{
		free((*mat)[l - 1]);
		(*mat)[l - 1] = NULL;
		l--;
	}
	free(*mat);
	*mat = NULL;
}

void		matrix_mul3_vec3(t_matrix mat, t_vec3 *v)
{
	MATRIX_T	tmp[1][3];
	t_u32		j;

	j = 0;
	tmp[0][0] = 0;
	tmp[0][1] = 0;
	tmp[0][2] = 0;
	while (j < 3)
	{
		tmp[0][j] += mat[0][j] * v->x;
		tmp[0][j] += mat[1][j] * v->y;
		tmp[0][j] += mat[2][j] * v->z;
		j++;
	}
	v->x = tmp[0][0];
	v->y = tmp[0][1];
	v->z = tmp[0][2];
}

void		matrix_cpy3(t_matrix m1, t_matrix m2)
{
	t_u32		i;
	t_u32		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			m1[i][j] = m2[i][j];
			j++;
		}
		i++;
	}
}

void		matrix_mul3(t_matrix m1, t_matrix m2)
{
	t_matrix	tmp;
	t_u32		i;
	t_u32		j;

	if ((tmp = matrix_new(MATRIX_33, MATRIX_NOSET)) == NULL)
		return ;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			tmp[i][j] = m1[i][0] * m2[0][j];
			tmp[i][j] += m1[i][1] * m2[1][j];
			tmp[i][j] += m1[i][2] * m2[2][j];
			j++;
		}
		i++;
	}
	matrix_cpy3(m1, tmp);
	matrix_del(MATRIX_33, &tmp);
}
