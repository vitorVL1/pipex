# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlima <vlima@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 11:27:45 by vlima             #+#    #+#              #
#    Updated: 2023/06/28 15:04:27 by vlima            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = 
RM = rm -f

SRC = 	pipex.c utils.c utils1.c

all:			$(NAME)

$(NAME):		
				$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(NAME) 

clean:
				$(RM) $(NAME)

fclean: 		clean
				

re:		fclean	$(NAME)

.PHONY: all clean fclean re