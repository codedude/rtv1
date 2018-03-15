/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:29:55 by valentin          #+#    #+#             */
/*   Updated: 2018/03/15 11:50:31 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rtv1.h"

/*
** Max map filsize : 4Mo
*/

# define BUFF_SIZE	4194304
# define BUFF_READ	4096

/*
** Tokens
*/

# define T_COMMENT	'#'

/*
** reader.c
*/

char		*read_map(char *filename);
char		**cut_map(char *map);

/*
** parser.c
*/

int			parse_map(t_env *env, char *map);

#endif
