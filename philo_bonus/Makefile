NAME 	=	philo

CFILES	=	philo_bonus.c			src/begin_bonus.c\
			src/checking_bonus.c	src/steps_bonus.c\
			src/timing_bonus.c		src/tools.c\
			src/validate.c

HEADER	= 	philo_bonus.h

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
