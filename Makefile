NAME        := cub3D
CC        := gcc
FLAGS    := -g -Wall -Wextra -Werror 

SRCS        :=      cub3d.c \
			init.c \
			init_extra.c \
			draw.c \
			draw_line.c \
			draw_extra.c \
			rays.c \
			controls.c \
			player_move.c \
			player_direction.c \
			player_rotate.c \
			map.c \
			textures.c \
			floor_ceil.c \
			file_read_utils.c \
  			get_next_line.c \
  			get_next_line_utils.c \
			utils.c \
			utils_extra.c \
			free.c \
			checker.c
                       
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

UNAME		:=	$(shell uname)



$(NAME): ${OBJS}
			@ $(MAKE) -C mlx_linux all
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(OBJS) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm

all:		${NAME}


clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1

fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean 
			

re:			fclean all

.PHONY:		all clean fclean re


