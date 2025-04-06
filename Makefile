NAME = addnum

CC = gcc

RM = rm -f

CFLAGS = -g3 -Wall -Wextra -Werror -pthread

SRCS = addnum.c
OBJS = ${SRCS:.c=.o}

clean:
    ${RM} ${OBJS}

fclean: clean
    ${RM} ${NAME}

re: fclean all


