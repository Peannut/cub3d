# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 22:20:51 by zoukaddo          #+#    #+#              #
#    Updated: 2023/02/22 19:03:00 by abouhaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3d

SRCS			= main.c ./src/drawing.c ./src/map_reader.c ./src/parser.c\
				./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c \
				./src/update.c ./src/casting_rays.c

OBJS			= $(SRCS:.c=.o)

CC				= cc -g 

RM				= rm -f


#MlX_PATH 		= -L/usr/lib -lXext -lX11 -lm -lz


#CFLAGS			= #-Wall -Wextra -Werror
CFLAGS			=  -I minilibx -framework OpenGl -framework Appkit -fsanitize=address -g


all:			$(NAME)

$(NAME):		$(OBJS)
				
				$(CC) ${OBJS} minilibx/libmlx.a $(CFLAGS) -o ${NAME}
				
clean:
				$(RM) $(OBJS) 
		

fclean:			clean
				$(RM) $(NAME)
				
re:				fclean $(NAME)

.PHONY:			all clean fclean re