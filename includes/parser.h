/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:29:55 by valentin          #+#    #+#             */
/*   Updated: 2018/03/24 18:13:23 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rtv1.h"
# include "objects.h"

/*
** Max map filsize : 4Mo
*/

# define BUFF_SIZE				(1 * 1024 * 1024)
# define BUFF_READ				4096

# define OBJECT_SIZE			7
# define OBJECT_DETAILS_SIZE	12

/*
** Type counter order
** plane, sphere, cone, cylinder, light, canvas, camera
** -----------------------------
** Counter order list
** width, height, background, ang, orig, fov,
** pos, dir, size, color, intensity, phong
*/

/*
** Tokens
*/

# define T_COMMENT		'#'
# define T_OPEN			'{'
# define T_CLOSE		'}'
# define T_SEPAR		'='

typedef struct	s_parse_type {
	char		*name;
	int			(*f)(void *data, char **strs);
	char		*types;
	size_t		size;
}				t_parse_type;

/*
** reader.c
*/

int				check_map(char *str);
char			*read_map(char *filename);
char			**cut_map(char *map);
int				trim_content(char **dest);

/*
** parser.c
*/

int				parse_map(t_env *env, char *map);

/*
** parse_type.c
*/

int				parse_global(t_env *env, char **str, int type);
t_parse_type	*get_parse_funs(void);

/*
** parse_details.c
*/

int				parse_details(t_env *env, int id, char *line, t_object *obj);

/*
** parse_funsX.c
*/

int				parse_t_width(void *data, char **strs);
int				parse_t_height(void *data, char **strs);
int				parse_t_background(void *data, char **strs);
int				parse_t_ang(void *data, char **strs);
int				parse_t_orig(void *data, char **strs);
int				parse_t_fov(void *data, char **strs);
int				parse_t_pos(void *data, char **strs);
int				parse_t_dir(void *data, char **strs);
int				parse_t_size(void *data, char **strs);
int				parse_t_color(void *data, char **strs);
int				parse_t_intensity(void *data, char **strs);
int				parse_t_phong(void *data, char **strs);

#endif
