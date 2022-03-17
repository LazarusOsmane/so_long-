SRC = main.c parse.c #map.c
OBJ = ${SRC:%.c=%.o}
CFLAG = -g3 -Wall -Wextra -Werror
CC = gcc
UNAME := $(shell uname)
all: so_long

ifeq ($(UNAME), Linux)
so_long: $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -lreadline -o $@ libft/libft.a minilibx-linux/libmlx_Linux.a -lXext -lX11 -I./minilibx_linux/ 

%.o: %.c
	cd libft/ && make && cd ..
	cd minilibx-linux && make && cd ../
	$(CC) $(CFLAG) -c $^ -o $@
endif

ifeq ($(UNAME), Darwin)
so_long: $(OBJ)
	$(CC) $(CFLAG) $(OBJ) minilibx_opengl_20191021/libmlx.a -lreadline -o $@  -lmlx -framework OpenGL -framework AppKit  -I./minilibx_opengl_20191021/ 

%.o: %.c
	cd minilibx_opengl_20191021/ && make && cd ../
	$(CC) $(CFLAG) -c $< -o $@
endif

clean: 
	rm *.o

fclean:
	rm *.o so_long

re: fclean all
	cd libft && make re && cd ..

.PHONY: all fclean clean re
