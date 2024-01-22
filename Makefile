CC			=		CC

CFLAGS		=		-Wall -Wextra -Werror -I./include

SRC			=		main.c parsing/mainParser.c \
					get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ			=		$(SRC:.c=.o)

HEADER		=		./include/cub3d.h include/get_next_line.h libft/libft.h

NAME		=		cub3D

all:		$(NAME)

$(NAME):	$(OBJ)
			make -C libft
			$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME) -L./minilibx -lmlx -framework OpenGL -framework AppKit

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			make fclean -C libft
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re