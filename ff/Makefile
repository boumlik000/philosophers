NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread

SRCS = philo.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@-$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@-$(CC) $(CFLAGS) -c $< -o $@

clean:
	@-rm -f $(OBJS)
	@-echo "clean done"

fclean: clean
	@-rm -f $(NAME)
	@-echo "fclean done"

re: fclean 
	@-$(MAKE) all 
	@-$(MAKE) clean 

# .PHONY: all clean fclean re
.SECONDARY: $(OBJC)
