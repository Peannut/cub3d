# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 22:20:51 by zoukaddo          #+#    #+#              #
#    Updated: 2023/03/12 19:47:00 by abouhaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc 

CFLAGS			=  -I minilibx -framework OpenGl -framework Appkit -fsanitize=address -g

NAME			= cub3d

LIBFT			= libft/libft.a
SRCS			= main.c ./src/drawing.c ./src/map_reader.c ./src/parser.c \
					./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c \
					./src/update.c ./src/casting_rays.c parsemap.c

OBJS			= $(SRCS:.c=.o)

all:			$(NAME)
RM				= rm -f


$(NAME):		$(LIBFT) $(OBJS)
				
				$(CC) ${OBJS} minilibx/libmlx.a $(CFLAGS) -o  ${NAME} $(LIBFT)

$(LIBFT):
	make -C libft
#MlX_PATH 		= -L/usr/lib -lXext -lX11 -lm -lz


#CFLAGS			= #-Wall -Wextra -Werror

				
clean:
				$(RM) $(OBJS)
				make clean -C libft
		

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(LIBFT)
				
re:				fclean all

.PHONY:			all clean fclean re