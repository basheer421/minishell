/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:19:02 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/23 18:19:02 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include  <errno.h>
# include "libft.h"

typedef struct s_alloced
{
	int		pipes[2][2];
	// char	**cmd;
	char	*path;
	char	**envp;
}	t_alloced;

# define WRONG_ARG_COUNT	"Incorrect number of arguments"
# define EMPTY_STRING_ERR	"Command cannot be an empty string"
# define CMD_ERR			"command not found"
# define PERMISSION_ERR		"permission denied"
# define NO_FILE_ERR		"No such file or directory"

char		**parse_path(char **envp);
char		*get_pathname(char *cmd_name, char **envp);
// int			redirect_file(char *file_name, int pipe_end, int open_flags);
void		free_strs(char **args, char *str, int index);
int			check_err(char *func_name, int ret_value);
void		exit_msg(char *head, char *err_msg, int err_code, t_alloced *mem);

#endif
