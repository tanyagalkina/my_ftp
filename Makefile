##
## EPITECH PROJECT, 2020
## NWP, myftp
## File description:
## Makefile
##

NAME	= myftp

CC	= gcc

RM	= rm -f

SRCS	=	./src/main.c \

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/
CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re