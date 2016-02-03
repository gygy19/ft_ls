# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/23 22:02:17 by jguyet            #+#    #+#              #
#    Updated: 2016/02/02 21:33:10 by jguyet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_ls.c\
	  flaging.c\
	  print_error.c\
	  sorting_args.c\
	  sort_func.c\
	  print_files.c\
	  print_dirs.c\
	  print_length.c\
	  tools.c\
	  tools_two.c\
	  tools_three.c\
	  tools_fourth.c\
	  print_l.c\
	  print_l_two.c\
	  print_rdev.c\
	  colors.c

NAME = ft_ls

FLAGS = -Werror -Wextra -Wall

SRCO = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc -I ./includes $(SRC) $(FLAGS) -c
	@gcc -I ./includes -L libft $(SRCO) $(FLAGS) -o $(NAME) -lft
	@echo "Compiling" [ $(NAME) ] "\033[32mSUCCESS\033[00m"

clean:
	@make -C libft fclean
	@rm -rf $(SRCO)
	@echo "Cleaning" [ $(NAME) ] "..." "\033[35mOK\033[00m"

fclean:		clean
	@rm -rf $(NAME)

re:		fclean all

.PHONY: all clean fclean re

