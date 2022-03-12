SRC = main.c map.c
OBJ = ${SRC:%.c=%.o}
CFLAG = -g3 -Wall -Wextra -Werror -I./
$(CC) = gcc

all: so_long

so_long: $(OBJ)
	  make bonus -C ./libft
		$(CC) $(CFLAG) $(OBJ) ./libft/libft.a -lreadline -o $@ minilibx-linux/libmlx_Linux.a -lXext -lX11 -I./minilibx_linux/ 
	#$(CC) $(CFLAG) $^ -o $@ minilibx-linux/libmlx_Linux.a -lXext -lX11 -I./minilibx_linux/ 

%.o: %.c
	cd minilibx-linux && make && cd ../
	$(CC) $(CFLAG) -c $^ 

clean: 
	rm *.o

fclean:
	rm *.o so_long

re: fclean all

.PHONY: all fclean clean re
