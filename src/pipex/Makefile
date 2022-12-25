# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bammar <bammar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 17:34:11 by mfirdous          #+#    #+#              #
#    Updated: 2022/12/25 18:13:49 by bammar           ###   ########.fr        #
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
			${CC} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT}:	
			${MAKE} -C libft
			
all:		${NAME}

bonus:		${LIBFT} ${B_OBJS}
			${CC} ${B_OBJS} ${LIBFT} -o ${NAME}

clean:	
			rm -f ${OBJS}
			rm -f ${B_OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
