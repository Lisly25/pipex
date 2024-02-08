# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 15:34:44 by skorbai           #+#    #+#              #
#    Updated: 2024/02/08 16:56:26 by skorbai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FLAGS = -Wall -Wextra -Werror

SRCS = main.c \
	init_utils.c \
	fork_utils.c \
	bash_errors.c \
	bash_errors_pt2.c \
	error_handling.c \
	empty_str_errors.c \
	exec_first_command.c \
	exec_second_command.c \
	exec_find_path.c \
	exec_utils.c \
	exec_abs_path.c

BONUS_SRCS = main_bonus.c \
	init_utils_bonus.c \
	fork_utils_bonus.c \
	bash_errors_bonus.c \
	bash_errors_pt2_bonus.c \
	error_handling_bonus.c \
	empty_str_errors_bonus.c \
	heredoc_bonus.c \
	exec_second_command_bonus.c \
	exec_find_path_bonus.c \
	exec_utils_bonus.c \
	exec_abs_path_bonus.c \
	vector_bonus.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

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
	rm -f $(BONUS_OBJS)
	@rm -f .bonus
	make clean -C ./libft

fclean: clean 
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

bonus: .bonus

.bonus: $(BONUS_OBJS) $(LIBFT)
	cc $(C_FLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)
	@touch .bonus

my_make: all
	make clean

fsanitize: $(OBJS) $(LIBFT)
	cc $(C_FLAGS) -fsanitize=address -g $(OBJS) $(LIBFT) -o $(NAME)
	make clean

.PHONY: all clean fclean re my_make fsanitize bonus
	