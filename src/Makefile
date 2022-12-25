# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bammar <bammar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 22:32:59 by bammar            #+#    #+#              #
#    Updated: 2022/12/25 18:13:34 by bammar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

FILES	=	minishell.c 	\
			ms_line_read.c	\

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

LINKS	=	-lreadline

OBJS	= $(FILES:.c=.o)

HEADER	=	../include

LIBFT	=	libft/libft.a

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HEADER}

all: 		$(NAME)

$(NAME):	$(OBJS)
			${MAKE} -C libft
			${MAKE} -C pipex
			$(CC) $(LINKS) $(OBJS) $(CFLAGS) $(LIBFT) -o $(NAME)

clean:
			${MAKE} -C libft clean
			${MAKE} -C pipex clean
			rm -f $(OBJS)

fclean:	clean
			${MAKE} -C libft fclean
			${MAKE} -C pipex fclean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
