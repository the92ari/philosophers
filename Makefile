SRCS = main.c ft_atoi.c activity.c time.c threadfunctions.c setstructs.c

OBJS = $(SRCS:.c=.o)

RM = rm -rf

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = philo

all:		$(NAME)

$(NAME):	$(SRCS)
			$(CC) $(FLAGS) $(SRCS) -pthread -o $(NAME)

clean:	
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all