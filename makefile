# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnave <tnave@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 14:32:47 by tnave             #+#    #+#              #
#    Updated: 2021/10/11 12:20:09 by tnave            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =  ft_lst.c			\
		exit_error.c		\
		ft_split.c			\
		parsing.c 			\
		pipex.c 			\
		utils_two.c 		\
		utils.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I ./include/

HEADER = -I ./includes/

OBJ = $(SRCS:%.c=%.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

all: $(NAME)

%.o%.c:
	$(CC) -c $(CFLAGS) -I $(HEADER) $< -o ${<:.c=.o}

clean:
	rm -f $(OBJ) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re