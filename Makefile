NAME := cube
OBJ :=
		obj/main.o \
		obj/parser.o \
CFLAGS := -Werror -Wextra -Wall
DEBUG := -fsanitize=address -g3
CC := gcc
LIBFT := includes/libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT): 
	make -c ./includes/libft

$(NAME): $(OBJ)
	
