SRC	=	main.c parsing/parser.c get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c rendering/renderer.c \
		rendering/drawer.c rendering/tools.c

OBJ	=	$(SRC:.c=.o)

HEADERS	=	headers/cub3d.h headers/get_next_line.h headers/libft.h

NAME	=	cub3D

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror


all:	$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/brew/opt/glfw/lib/" -framework OpenGL -framework AppKit

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C ./libft
	rm -f $(OBJ)

fclean:	clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re