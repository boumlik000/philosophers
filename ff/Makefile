NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread
FT_PRINTF = ./ft_printf/libftprintf.a
SRCS = philo.c data_init.c time.c print.c \
		destroy.c philo_behave.c monitor.c utils.c single_case.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(FT_PRINTF) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "clean done"

fclean: clean
	@rm -f $(NAME)
	@echo "fclean done"

re: fclean all
	@echo "re done" 

.PHONY: all clean fclean re
