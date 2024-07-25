CFLAGS = -Wall -Werror -Wextra

CC = cc

SOURCES = fractol.c fractol_utils.c main.c handler.c math_utils.c

OBJECTS = $(SOURCES:.c=.o)

NAME = fractol

UNAME		:=	$(shell uname)

all: $(NAME)

ifeq ($(UNAME), Darwin)
%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJECTS)
	$(MAKE) all -C mlx
	$(CC) $(OBJECTS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "\n\n========== Fractol ==========\n"
	@echo "\tFor Mandlebort: ./$(NAME) mandelbrot"
	@echo "\tFor Julia: ./$(NAME) julia <float x> <float y>"

endif

ifeq ($(UNAME), Linux)
%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@
	
$(NAME): $(OBJECTS)
	$(MAKE) all -C mlx_linux
	$(CC) $(OBJECTS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "\n\n========== Fractol ==========\n"
	@echo "\tFor Mandlebort: ./$(NAME) mandelbrot"
	@echo "\tFor Julia: ./$(NAME) julia <float x> <float y>"

endif

clean:
	rm -f $(OBJECTS)
	$(MAKE) clean -C mlx
	# $(MAKE) clean -C mlx_linux

fclean: clean
	rm -f $(NAME)

re: fclean all