# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 22:20:51 by zoukaddo          #+#    #+#              #
#    Updated: 2022/12/05 22:22:16 by zoukaddo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3d

SRCS			= main.c

OBJS			= $(SRCS:.c=.o)

CC				= cc -g 

RM				= rm -f


MlX_PATH 		= -L/usr/lib -lXext -lX11 -lm -lz


CFLAGS			= #-Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJS)
				
				$(CC) ${OBJS} $(CFLAGS) minilibx-linux/libmlx.a -o ${NAME} $(MlX_PATH) 
clean:
				$(RM) $(OBJS) 
		

fclean:			clean
				$(RM) $(NAME)
				
re:				fclean $(NAME)

.PHONY:			all clean fclean re