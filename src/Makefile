# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bammar <bammar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 22:32:59 by bammar            #+#    #+#              #
#    Updated: 2023/01/18 16:19:41 by bammar           ###   ########.fr        #
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
				ms_init.c \
				ms_line/ms_line_read.c \
				ms_line/ms_line_isempty.c \
				ms_line/ms_line_contains_commands.c	\
				ms_line/ms_line_expand_vars.c \
				ms_pipes/ms_pipes_count.c \
				ms_pipes/ms_pipes_positions.c	\
				ms_pipes/ms_pipes_divide.c \
				ms_error/ms_error_invalid_char.c \
				ms_tokenization/ms_contains_input.c \
				ms_tokenization/ms_get_next_input.c \
				ms_tokenization/ms_contains_cmd.c \
				ms_tokenization/ms_get_cmd.c \
				ms_tokenization/ms_get_fullcmd.c \
				ms_tokenization/ms_contains_output.c \
				ms_tokenization/ms_get_next_output.c \
				ms_tokenization/ms_get_input_fd.c \
				ms_tokenization/ms_split_utils.c \
				ms_tokenization/ms_split_with_no_quotes.c \
				ms_builtins/ms_handle_builtins.c \
				ms_builtins/ms_echo.c \
				ms_builtins/ms_pwd.c \
				ms_builtins/ms_cd.c \
				ms_builtins/ms_env.c \
				ms_builtins/ms_export.c \
				ms_builtins/ms_unset.c \
				ms_builtins/ms_exit.c \
				ms_error/ms_errno_check.c \
				ms_command_chunk/ms_command_chunks_get.c \
				

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g -Ofast

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
