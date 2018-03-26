# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/03/26 20:12:50 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	rtv1
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft
LIBTPOOLD	=	libtpool
MLXD		=	minilibx_macos
IMG			=	saved_img

SRCS		=	$(SRCD)/main.c $(SRCD)/ft_mlx.c $(SRCD)/ft_pixel.c \
				$(SRCD)/env.c $(SRCD)/compute.c $(SRCD)/binds.c \
				$(SRCD)/binds2.c $(SRCD)/objects.c $(SRCD)/objects_set.c \
				$(SRCD)/vec3_1.c $(SRCD)/vec3_2.c $(SRCD)/vec3_3.c \
				$(SRCD)/vec3_4.c $(SRCD)/matrix_1.c $(SRCD)/matrix_2.c \
				$(SRCD)/matrix_3.c $(SRCD)/export_bmp.c $(SRCD)/export_bmp2.c \
				$(SRCD)/rt.c $(SRCD)/rt_norm.c $(SRCD)/rt_utils.c \
				$(SRCD)/rt_convert.c $(SRCD)/rt_intersect.c $(SRCD)/rt_color.c \
				$(SRCD)/reader.c $(SRCD)/parser.c $(SRCD)/parse_type.c \
				$(SRCD)/parse_funs1.c $(SRCD)/parse_funs2.c \
				$(SRCD)/parse_funs3.c $(SRCD)/parse_details.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(INCD) -O3 -flto -march=native -g \
				-I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes -I$(MLXD)
LDFLAGS		+=	-Wextra -Wall -Wno-unused-result
LDLIBS		+=	-L$(LIBFTD) -lft -L$(LIBTPOOLD) -ltpool -L$(MLXD) -lmlx -lm \
				-framework OpenGL -framework AppKit

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	make -C $(LIBTPOOLD)
	make -C $(MLXD)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	make -C $(LIBFTD) clean
	make -C $(LIBTPOOLD) clean
	make -C $(MLXD) clean
	@rm -vf $(OBJS)

fclean: clean
	make -C $(LIBFTD) __fclean
	make -C $(LIBTPOOLD) __fclean
	@rm -vf $(MLXD)/libmlx.a
	@rm -vf $(NAME)

re: fclean all

rer:
	@rm -f $(NAME)
	@rm -f $(OBJS)
	make $(NAME)

clean_saved:
	rm -f $(IMG)/*.bmp