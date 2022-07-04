NAME 	=	philo

CFILES	=	philo.c			src/begin.c\
			src/checking.c	src/forks.c\
			src/free.c		src/steps.c\
			src/timing.c	src/validate.c

HEADER	= 	philo.h

OBJECTS	=	$(CFILES:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -pthread

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o 	:	%.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	rm -f $(OBJECTS)

fclean	:	clean
	rm -f $(NAME)

re		:	fclean all
