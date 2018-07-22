# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwright <mlwright09@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/29 19:48:20 by mwright           #+#    #+#              #
#    Updated: 2017/05/05 23:13:25 by mwright          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = a_database
SRCS = delete_record.c labels.c main.c nodestofile.c query_record.c \
	  update_details.c update_record.c validate_query.c ./libft/libft.a
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): 
	make all -C ./libft
	$(CC) -o $(NAME) $(CFLAGS) $(SRCS)

clean:
	rm -rf $(OBJS)
	make clean -C ./libft

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
