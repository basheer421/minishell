# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 22:32:59 by bammar            #+#    #+#              #
#    Updated: 2023/03/04 13:52:12 by mfirdous         ###   ########.fr        #
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
				src/ms_line/ms_add_spaces.c \
				src/ms_line/ms_line_iscomplete.c \
				src/ms_line/ms_expand_vars_utils.c \
				src/ms_line/ms_line_expand_vars.c \
				src/ms_tokenization/ms_contains_redirect.c \
				src/ms_tokenization/ms_get_next_redirect.c \
				src/ms_tokenization/ms_contains_cmd.c \
				src/ms_tokenization/ms_get_cmd.c \
				src/ms_tokenization/ms_get_fullcmd.c \
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
				src/ms_builtins/ms_is_valid_identifier.c \
				src/ms_builtins/ms_builtinredir_utils.c \
				src/ms_command_chunk/ms_command_chunks_get.c \
				src/ms_error/ms_error_utils.c \
				src/ms_exec/ms_exec_cmds.c \
				src/ms_exec/ms_get_path.c \
				src/ms_exec/ms_pipes_count.c \
				src/ms_exec/ms_pipex_utils.c \
				src/ms_exec/ms_pipex.c \
				src/ms_exec/ms_redirect_in.c \
				src/ms_exec/ms_redirect_out.c \
				src/ms_signal/ms_signal_handler.c \
				src/ms_signal/ms_get_sig_status.c 

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -I/usr/local/opt/readline/include -g3

LINKS	=	-lreadline -L/usr/local/opt/readline/lib

OBJS	= $(FILES:.c=.o)

HEADER	=	include

LIBFT	=	src/libft/libft.a

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HEADER}

all: 		$(NAME)

$(NAME):	$(OBJS)
			${MAKE} -C src/libft
			$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(LINKS) -o $(NAME)

clean:
			${MAKE} -C src/libft clean
			/bin/rm -f $(OBJS)

fclean:		clean
			${MAKE} -C src/libft fclean
			/bin/rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
