# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 15:34:44 by skorbai           #+#    #+#              #
#    Updated: 2024/01/29 15:41:01 by skorbai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FLAGS = -Wall -Wextra -Werror

SRCS = main.c \
	fork_utils.c \
	error_handling.c \
	exec_first_command.c \
	exec_second_command.c \
	exec_utils.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

NAME = pipex

all: $(NAME)

$(LIBFT) :
	make -C ./libft

%.o: %.c
	cc $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(LIBFT)
	cc $(C_FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C ./libft

fclean: clean 
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

my_make: all
	make clean

fsanitize: $(OBJS) $(LIBFT)
	cc $(C_FLAGS) -g -fsanitize=address $(OBJS) $(LIBFT) -o $(NAME)
	make clean

.PHONY: all clean fclean re my_make fsanitize
	