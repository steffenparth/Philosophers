NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra 
# -g -fsanitize=thread

SRC = philo.c utils.c preperation.c time_related.c thread_stuff.c error.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re