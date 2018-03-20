/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:29:55 by valentin          #+#    #+#             */
/*   Updated: 2018/03/20 13:04:17 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rtv1.h"

/*
** Max map filsize : 4Mo
*/

# define BUFF_SIZE		1048576
# define BUFF_READ		4096

# define OBJECT_SIZE			7
# define OBJECT_DETAILS_SIZE	11

/*
** Type counter order
** canvas, camera, light, plan, sphere, cylinder, cone
** -----------------------------
** Counter order list
** width, height, background, ang, fov, pos, dir, size, color, intensity, phong
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
	int			(*f)(t_env *, char **strs);
	char		*types;
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

int				parse_details(t_env *env, int id, char *line);

/*
** parse_funsX.c
*/

int				parse_t_width(t_env *env, char **strs);
int				parse_t_height(t_env *env, char **strs);
int				parse_t_background(t_env *env, char **strs);
int				parse_t_ang(t_env *env, char **strs);
int				parse_t_fov(t_env *env, char **strs);
int				parse_t_pos(t_env *env, char **strs);
int				parse_t_dir(t_env *env, char **strs);
int				parse_t_size(t_env *env, char **strs);
int				parse_t_color(t_env *env, char **strs);
int				parse_t_intensity(t_env *env, char **strs);
int				parse_t_phong(t_env *env, char **strs);

#endif
