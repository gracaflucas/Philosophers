CFLAGS = -Wall -Werror -Wextra -g -pthread

NAME = philo

CC = cc
RM = rm -rf

SRC = philo.c\
	parsing.c\
	routines.c\
	utils.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
