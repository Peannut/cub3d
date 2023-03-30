# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 22:20:51 by zoukaddo          #+#    #+#              #
#    Updated: 2023/03/30 16:49:11 by zoukaddo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc 

CFLAGS			=  -I minilibx -framework OpenGl -framework Appkit

NAME			= cub3d

LIBFT			= libft/libft.a

SRCS			= main.c ./src/drawing.c ./src/parser.c ./src/parsing_alloc.c ./src/colors.c \
					./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c \
					./src/update.c ./src/casting_rays.c ./src/vertical_rays.c ./src/minimap.c ./src/mouse.c \
					./src/directions.c ./src/floor_ceiling.c ./src/ft_check.c ./src/ft_free.c ./src/ft_initialize.c ./src/ft_utils.c \
					./src/map_utils.c ./src/ft_error.c ./src/horizontal.c ./src/minimap_utils.c ./src/casting_rays_utils.c \
					./src/casting_utils.c ./src/update_utils.c ./src/utils.c

OBJS			= $(SRCS:.c=.o)

RM				= rm -f


#MlX_PATH 		= -L/usr/lib -lXext -lX11 -lm -lz



all:			$(NAME)

$(NAME):		$(OBJS)
				
				$(CC) ${OBJS} minilibx/libmlx.a $(CFLAGS) libft/libft.a -o $(NAME)
				
clean:
				$(RM) $(OBJS)
				make clean -C libft
		

fclean:			clean
				$(RM) $(NAME)
				
re:				fclean all

.PHONY:			all clean fclean re