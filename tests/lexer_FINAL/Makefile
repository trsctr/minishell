# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 20:59:29 by akoskine          #+#    #+#              #
#    Updated: 2023/09/05 15:33:58 by akoskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = lexer.c

NAME = lexer
LIBFT = ./libft/libft.a
FT_PRINTF = ./libft/ft_printf/libftprintf.a
RLFLAG = -lreadline -L ~/.brew/opt/readline/lib -I~/.brew/opt/readline/include
O_SRC = ${SRC:.c=.o}

all: $(LIBFT) $(NAME)

$(NAME): $(SRC)
	cc -Wall -Wextra -Werror $(LIBFT) $(FT_PRINTF) $(RLFLAG) $(SRC) -o $(NAME)

$(LIBFT) :
	make -C ./libft

clean:
	rm -rf $(O_SRC)
	make clean -C ./libft

fclean:
	rm -rf $(NAME) $(O_SRC)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
