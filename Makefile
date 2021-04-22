##
## EPITECH PROJECT, 2020
## NWP, myftp
## File description:
## Makefile
##

NAME	= myftp

CC	= gcc

RM	= rm -f

SRCS	=	./src/main.c 		\
		./src/server.c		\
		./src/commands.c	\
		./src/handle_conns.c	\
		./src/cmd_handler.c	\
		./src/my_str_to_word_array.c	\
		./src/my_str_isprintable.c	\
		./src/pasv.c		\
		./src/get_input.c	\

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/
CFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re