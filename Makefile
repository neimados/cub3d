NAME = cub3D
NAME_BONUS = cub3D_bonus

SRC = ./srcs/cub3d.c ./srcs/utils.c ./srcs/get_next_line.c ./srcs/get_next_line_utils.c \
./srcs/split.c ./srcs/utils2.c ./srcs/error.c ./srcs/utils3.c ./srcs/check.c ./srcs/check2.c \
./srcs/parse.c ./srcs/parse_utils.c ./srcs/exec_utils1.c ./srcs/minimap.c ./srcs/display.c \
./srcs/texture.c ./srcs/texture_bonus.c ./srcs/display_utils.c ./srcs/exec_utils2.c

OBJS = ${SRC:.c=.o}

CC		= gcc
CFLAGS = -Wall -Wextra -Werror
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
		${RM} ${NAME} ${NAME_BONUS}

re:		fclean all

bonus: ${NAME_BONUS}

$(NAME_BONUS): ${OBJS}
		make -C ${MINILIBX}
		${CC} ${CFLAGS} -framework OpenGL -framework AppKit -o $@ $^ minilibx/libmlx.a

.PHONY: all clean fclean re bonus