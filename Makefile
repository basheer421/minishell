# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 22:32:59 by bammar            #+#    #+#              #
#    Updated: 2023/01/23 21:13:28 by mfirdous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

FILES	=		src/minishell.c \
				src/ms_init.c \
				src/hashtable/ht_get.c \
				src/hashtable/ht_hash.c \
				src/hashtable/ht_new.c \
				src/hashtable/ht_set.c \
				src/hashtable/ht_remove.c \
				src/hashtable/ht_isempty.c \
				src/hashtable/ht_contains.c \
				src/hashtable/ht_replace.c \
				src/hashtable/ht_clear.c \
				src/hashtable/ht_destroy.c \
				src/ms_line/ms_line_clean.c \
				src/ms_line/ms_line_read.c \
				src/ms_line/ms_line_isempty.c \
				src/ms_line/ms_line_contains_commands.c	\
				src/ms_line/ms_expand_vars_utils.c \
				src/ms_line/ms_line_expand_vars.c \
				src/ms_pipes/ms_pipes_count.c \
				src/ms_pipes/ms_pipes_positions.c	\
				src/ms_pipes/ms_pipes_divide.c \
				src/ms_error/ms_errno_check.c \
				src/ms_tokenization/ms_contains_input.c \
				src/ms_tokenization/ms_get_next_input.c \
				src/ms_tokenization/ms_contains_cmd.c \
				src/ms_tokenization/ms_get_cmd.c \
				src/ms_tokenization/ms_get_fullcmd.c \
				src/ms_tokenization/ms_contains_output.c \
				src/ms_tokenization/ms_get_next_output.c \
				src/ms_tokenization/ms_get_input_fd.c \
				src/ms_tokenization/ms_get_output_fd.c \
				src/ms_tokenization/ms_split_utils.c \
				src/ms_tokenization/ms_split_with_no_quotes.c \
				src/ms_builtins/ms_handle_builtins.c \
				src/ms_builtins/ms_echo.c \
				src/ms_builtins/ms_pwd.c \
				src/ms_builtins/ms_cd.c \
				src/ms_builtins/ms_env.c \
				src/ms_builtins/ms_export.c \
				src/ms_builtins/ms_unset.c \
				src/ms_builtins/ms_exit.c \
				src/ms_command_chunk/ms_command_chunks_get.c \
				src/pipex/pipex.c \
				src/pipex/error_check.c \
				src/pipex/pipex_utils.c \
				src/ms_signal/ms_signal_handler.c 

CC		=	cc

# CFLAGS	=	-Wall -Wextra -Werror -g -Ofast
CFLAGS	=	-Wall -Wextra -g -Ofast

LINKS	=	-lreadline 

OBJS	= $(FILES:.c=.o)

HEADER	=	include

LIBFT	=	src/libft/libft.a

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HEADER}

all: 		$(NAME)

$(NAME):	$(OBJS)
			${MAKE} -C src/libft
#			${MAKE} -C src/pipex
			$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(LINKS) -o $(NAME)

clean:
			${MAKE} -C src/libft clean
#			${MAKE} -C src/pipex clean
			/bin/rm -f $(OBJS)

fclean:		clean
			${MAKE} -C src/libft fclean
#			${MAKE} -C src/pipex fclean
			/bin/rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
