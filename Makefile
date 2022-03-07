INC=minilibx
INC_LINUX=minilibx-linux
NAME= fdf
SRC = main.c read.c project.c drawline.c keys.c
FLAGS = -O3 -Wall -Wextra -Werror

all	:$(NAME)

$(NAME)	: $(SRC)
	gcc $(SRC) $(FLAGS) -I /usr/local/include -L /usr/local/lib \
               -l mlx -framework OpenGL -framework Appkit -o $(NAME)
linux	:
	gcc -g $(SRC) $(FLAGS) -L$(INC_LINUX) -lm -lmlx -lX11 -lXext -o $(NAME)

clean	:
	rm -f $(NAME) $(OBJ) *~ core *.core

re	: clean all
