SRC	=	main.c parsing/parser.c get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c rendering/renderer.c \

OBJ	=	$(SRC:.c=.o)

NAME	=	cub3D

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror


all:	$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a MLX42/build/libmlx42.a -lglfw -L"/Users/mdoulahi/brew/opt/glfw/lib/" -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C ./libft
	rm -f $(OBJ)

fclean:	clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re