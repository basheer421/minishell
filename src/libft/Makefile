# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 11:10:32 by mfirdous          #+#    #+#              #
#    Updated: 2022/07/18 11:48:18 by mfirdous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_isalpha.c	ft_isdigit.c	ft_isalnum.c	ft_isascii.c \
			ft_isprint.c 	ft_strlen.c		ft_memset.c		ft_bzero.c ft_memcpy.c \
			ft_memmove.c	ft_strlcpy.c	ft_strlcat.c	ft_toupper.c \
			ft_tolower.c	ft_strchr.c		ft_strrchr.c	ft_strncmp.c \
			ft_memchr.c		ft_memcmp.c		ft_strnstr.c	ft_atoi.c ft_calloc.c \
			ft_strdup.c		ft_substr.c		ft_strjoin.c	ft_strtrim.c ft_split.c \
			ft_itoa.c		ft_strmapi.c	ft_striteri.c	ft_putchar_fd.c \
			ft_putstr_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c \
			ft_printf.c		ft_printf_utils.c \
			get_next_line.c	get_next_line_utils.c \
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c 

HEADER	=	../../include

OBJS		= ${SRCS:.c=.o}

BOBJS 		= ${BSRCS:.c=.o}

NAME		= libft.a

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HEADER}

${NAME}:	${OBJS}
			ar crs ${NAME} ${OBJS}

all:		${NAME}

clean:
			/bin/rm -f ${OBJS}
			/bin/rm -f ${BOBJS}

fclean:		clean
			/bin/rm -f ${NAME}

re:			fclean all
			
.PHONY:		all clean fclean re
