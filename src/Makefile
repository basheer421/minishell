# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bammar <bammar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 22:32:59 by bammar            #+#    #+#              #
#    Updated: 2022/12/25 17:33:22 by bammar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = minishell.c 	\
		ms_line_read.c	\


CC		= cc

CFLAGS	= -Wall -Wextra -Werror

LINKS	= -lreadline

OBJS	= $(FILES:.c=.o)

HEADER	=	../include

LIBFT	= libft/libft.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HEADER}

all: $(NAME)

$(NAME): $(OBJS)
	(cd libft && make)
	(cd pipex && make)
	$(CC) $(LINKS) $(OBJS) $(CFLAGS) $(LIBFT) -o $(NAME)

clean:
	(cd libft && make clean)
	(cd pipex && make clean)
	rm -f $(OBJS)

fclean:	clean
	(cd libft && make fclean)
	(cd pipex && make fclean)
	rm -f $(NAME)

re:	fclean all
