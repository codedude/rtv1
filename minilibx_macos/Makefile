#
#

NOM		=	libmlx.a
SRC		= 	mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m \
			mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1	=	$(SRC:.c=.o)
OBJ		=	$(OBJ1:.m=.o)
CFLAGS	+=	-O3 -flto -march=native

all: $(NOM)

$(NOM):	$(OBJ)
	@ar rs $(NOM) $(OBJ)
	@echo "mlx - compiled"

clean:
	@rm -f $(OBJ) *~
	@rm -f mlx_app
	@echo "mlx - objects cleaned"

fclean: clean
	@rm -f $(NOM)
	@echo "mlx - lib cleaned"

__fclean:
	@rm -f $(NOM)
	@echo "mlx- lib cleaned"

re: clean all
