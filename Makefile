# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 22:20:51 by zoukaddo          #+#    #+#              #
#    Updated: 2023/03/31 15:13:30 by zoukaddo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

NAME		= cub3d

CFLAGS		= -Wall -Wextra -Werror -I./minilibx

SRCS		=	main.c ./src/drawing.c ./src/parser.c ./src/parsing_alloc.c ./src/colors.c \
				./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c \
				./src/update.c ./src/casting_rays.c ./src/vertical_rays.c ./src/minimap.c ./src/mouse.c \
				./src/directions.c ./src/floor_ceiling.c ./src/ft_check.c ./src/ft_free.c ./src/ft_initialize.c ./src/ft_utils.c \
				./src/map_utils.c ./src/ft_error.c ./src/horizontal.c ./src/minimap_utils.c ./src/casting_rays_utils.c \
				./src/casting_utils.c ./src/update_utils.c ./src/utils.c

LIBFT 		= libft/libft.a

RM			= rm -f

OBJS		= $(SRCS:.c=.o)

MINILIBX	= ./minilibx/libmlx.a

all : $(NAME)

bonus : all


$(NAME) : $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) -framework OpenGL -framework AppKit $(LIBFT) $(OBJS) $(MINILIBX) -o $(NAME)

$(MINILIBX):
	make -C minilibx &> /dev/null

$(LIBFT):
	make  -C libft/ > /dev/null

clean :
	$(RM) $(OBJS)
	make clean -C libft/ > /dev/null

fclean : clean
	$(RM) $(NAME)
	$(RM) libft/libft.a
	$(RM) $(MINILIBX)

re : fclean all

.PHONY : all clean fclean bonus re