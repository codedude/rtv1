/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_key.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 19:02:05 by vparis            #+#    #+#             */
/*   Updated: 2018/02/02 18:26:14 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_KEY_H
# define FT_MLX_KEY_H

/*
** Event hook
*/

# define E_KEY_DOWN		2
# define E_KEY_UP		3
# define E_MOUSE_DOWN	4
# define E_MOUSE_UP		5
# define E_MOUSE_MOVE	6
# define E_EXPOSE		12

/*
** Mouse, M_#
*/

# define M_LEFT		1
# define M_RIGHT	2
# define M_MID		3
# define M_UP		4
# define M_DOWN		5

/*
** Common, K_#
*/

# define K_A		0
# define K_B		11
# define K_C		8
# define K_D		2
# define K_E		14
# define K_F		3
# define K_G		5
# define K_H		4
# define K_I		34
# define K_J		38
# define K_K		40
# define K_L		37
# define K_M		46
# define K_N		45
# define K_O		31
# define K_P		35
# define K_Q		12
# define K_R		15
# define K_S		1
# define K_T		17
# define K_U		32
# define K_V		9
# define K_W		13
# define K_X		7
# define K_Y		16
# define K_Z		6

/*
** Control, K_#
** K_#R for right side
*/

# define K_SPACE	49
# define K_ENTER	36
# define K_TAB		48
# define K_DEL		51
# define K_ESC		53
# define K_CTRL		256
# define K_CTRLR	256
# define K_SHIFT	269
# define K_SHIFTR	258
# define K_ALT		261
# define K_ALTR		262
# define K_CMD		259
# define K_CMDR		260

/*
** Arrow, K_#
*/

# define K_LEFT		123
# define K_RIGHT	124
# define K_DOWN		125
# define K_UP		126

/*
** Normal number, K_#
*/

# define K_TILDE	50
# define K_1		18
# define K_2		19
# define K_3		20
# define K_4		21
# define K_5		23
# define K_6		22
# define K_7		26
# define K_8		28
# define K_9		25
# define K_0		29
# define K_MINUS	27
# define K_PLUS		24

/*
** Rigth PAD, K_P#
*/

# define K_P1		83
# define K_P2		84
# define K_P3		85
# define K_P4		86
# define K_P5		87
# define K_P6		88
# define K_P7		89
# define K_P8		91
# define K_P9		92
# define K_P0		82
# define K_PENTER	76
# define K_PPLUS	69
# define K_PMINUS	78
# define K_PMUL		67
# define K_PDIV		75
# define K_PEQ		81
# define K_PCLEAR	71

#endif
