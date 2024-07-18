NAME = philo

CFLAGS = -Wall -Werror -Wextra 
CC = cc

SRC = philo.c utils.c parsing.c

OBJC =  $(SRC:.c=.o)

all: $(NAME)

$(OBJC) : $(SRC)

$(NAME): $(OBJC) 
	@-$(CC) $(OBJC) -o $(NAME)

%.o: %.c
	@-$(CC) $(CFLAGS) -c $< -o $@

clean:
	@-rm -rf $(OBJC) 

fclean: clean
	@-rm -rf $(NAME) 

re: fclean 
	@-$(MAKE) all
	@-$(MAKE) clean
	

.SECONDARY:  $(OBJC) 