NAME = cub3D

SRC = ./srcs/cub3d.c ./srcs/utils.c ./srcs/get_next_line.c ./srcs/get_next_line_utils.c

OBJS = ${SRC:.c=.o}

CC		= gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
MINILIBX = ./minilibx/


%.o: %.c ./includes/cub3d.h Makefile
		${CC} ${CFLAGS} -c $< -o $@

all:	${NAME}

$(NAME): ${OBJS}
		make -C ${MINILIBX}
		${CC} ${CFLAGS} -framework OpenGL -framework AppKit -o $@ $^ minilibx/libmlx.a

clean:
		make clean -C ${MINILIBX}
		${RM} ${OBJS}
 
fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re 