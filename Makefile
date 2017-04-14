# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/27 18:05:12 by afeuerst          #+#    #+#              #
#    Updated: 2017/04/14 11:34:20 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g -O0 -fsanitize=address

C_SRC = $(shell find ./src/ -type f | grep "\.c")
O_SRC = $(C_SRC:.c=.o)
I = -I./includes -ltermcap -lpthread

PRINT = printf "\e[34m%-30s -->\e[32m> %-30s\n" $@ $<

all: $(NAME)

$(NAME):
	@clang $(I) $(C_SRC) shell.c -o $(NAME)
	@printf "%s is now available\n" $(NAME)

clean:
	@rm -rf $(O_SRC)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
