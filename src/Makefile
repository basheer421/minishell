# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bammar <bammar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 22:32:59 by bammar            #+#    #+#              #
#    Updated: 2023/01/02 19:03:15 by bammar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

FILES	=		minishell.c \
				hashtable/ht_get.c \
				hashtable/ht_hash.c \
				hashtable/ht_new.c \
				hashtable/ht_set.c \
				hashtable/ht_remove.c \
				hashtable/ht_isempty.c \
				hashtable/ht_contains.c \
				hashtable/ht_replace.c \
				hashtable/ht_clear.c \
				hashtable/ht_destroy.c \
				ms_line/ms_line_read.c \
				ms_init.c \
				ms_line/ms_line_contains_commands.c	\
				ms_pipes/ms_pipes_count.c \
				ms_pipes/ms_pipes_positions.c	\
				ms_pipes/ms_pipes_divide.c \
				ms_error/ms_error.c


CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

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
			$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(LINKS) -o $(NAME)

clean:
			${MAKE} -C libft clean
			${MAKE} -C pipex clean
			/bin/rm -f $(OBJS)

fclean:	clean
			${MAKE} -C libft fclean
			${MAKE} -C pipex fclean
			/bin/rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
