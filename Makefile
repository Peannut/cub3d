# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 22:20:51 by zoukaddo          #+#    #+#              #
#    Updated: 2023/01/09 04:56:51 by zoukaddo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3d

SRCS			= main.c ./src/drawing.c ./src/map_reader.c \
			./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c \
				./src/update.c ./src/casting_rays.c

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