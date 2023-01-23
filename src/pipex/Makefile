# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 17:34:11 by mfirdous          #+#    #+#              #
#    Updated: 2023/01/23 01:02:47 by mfirdous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	pipex.c pipex_utils.c error_check.c

B_SRCS	=	pipex_bonus.c pipex_utils.c error_check.c

OBJS	=	${SRCS:.c=.o}

B_OBJS	=	${B_SRCS:.c=.o}

HEADER	=	../../include

NAME	=	pipex

LIBFT	=	../libft/libft.a

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra -I ${HEADER}

.c.o:		
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME}:	${LIBFT} ${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT}:	
			${MAKE} -C libft
			
all:		${NAME}

bonus:		${LIBFT} ${B_OBJS}
			${CC} ${CFLAGS} ${B_OBJS} ${LIBFT} -o ${NAME}

clean:	
			/bin/rm -f ${OBJS}
			/bin/rm -f ${B_OBJS}

fclean:		clean
			/bin/rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
