# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/27 18:05:12 by afeuerst          #+#    #+#              #
#    Updated: 2017/04/27 18:02:21 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g -O0 -fsanitize=address

C_SRC = $(shell find ./src/ -type f | grep "\.c")
O_SRC = $(C_SRC:.c=.o)
I = -I./includes -ltermcap -lpthread

PRINT = @printf "\e[34m%-30s -->\e[32m> %-30s\n" $@ $<

all: $(NAME)

$(NAME):
	@clang $(FLAGS) $(I) $(C_SRC) shell.c -o $(NAME)
	@printf "\e[33m%s is now available\e[37m\n" $(NAME)

clean:
	@rm -rf $(O_SRC)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
