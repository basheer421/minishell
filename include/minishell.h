/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:30:21 by bammar            #+#    #+#             */
/*   Updated: 2023/02/12 10:39:39 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ht.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define UNEXPECTED_TOKEN 258
# define CMD_ERR			"command not found"
# define PERMISSION_ERR		"permission denied"
# define IS_A_DIR_ERR		"Is a directory"

extern int	g_exit_status;

/**
 * @brief 	when name is delim for heredoc, is_extra is set to true
 * 			when file is for append, is_extra is set to true
 */
typedef struct s_file
{
	char	*name;
	bool	is_extra;
}				t_file;

/**
 * @brief This is a command chunk, should be like this
 * {{ "< input cmd  >  output" }} or something like that, less or more
 * 
 */
typedef struct s_cmd_chunk
{
	char	**cmd;
	t_list	*inputs;
	t_list	*outputs;
	int		in_redir_fd;
	int		out_redir_fd;
}			t_cmd_chunk;

/**
 * @brief Stores a hash map of environment variables,
 *  and stores the current dir.
 * 	Note that current_dir is malloced and should be freed.
 */
typedef struct s_ms
{
	t_ht		*env_vars;
	t_cmd_chunk	**cur_cmd;
	int			*pids;
	// char	*current_dir;
}			t_ms;

/**
 * @brief struct type for parsing
 * ; dquotes is for double quotes.
*/
typedef struct s_inside2
{
	bool	quotes;
	bool	dquotes;
	bool	var;
	char	*value;
}			t_inside2;

// helper for split
typedef struct s_split
{
	char	*line;
	char	c;
	char	**content;
	int		*positions;
	size_t	content_size;
}			t_split_vars;

// helper for split
typedef struct s_split_postions
{
	int		current_index;
	int		*positions;
	bool	inside_quotes;
	bool	inside_dquotes;
}			t_split_postions;

// allocated memory and open fds for execution
typedef struct s_alloced
{
	int		pipes[2][2];
	char	*path;
	char	**envp;
	t_ms	*shell;
}	t_alloced;

/**
 * @brief Reads the environment variables and stores them inside a struct.
 * 	Also gets the current working dir
 * 
 * @param envp enviroment variables from main() fucntion
 * @return mini shell struct pointer (t_ms *)
 */
t_ms		*ms_init(char **envp);

/**
 * @brief Destroys and frees everything inside the given shell (t_ms).
 * 
 * @param shell 
 */
void		ms_destroy(t_ms *shell);

/**
 * @brief Reads the command line and does the main functions,
 * 		which are catching signels and executing commands.
 * 
 * @param prompt desired prompt
 * @return Error code
 */
int			ms_line_read(const char *prompt, t_ms *shell);

/**
 * @brief Tells if the line is empty.
 * 
 * @param line user input
 * @return boolean, true if it's empty.
 */
bool		ms_line_isempty(char *line);

/**
 * @brief tells if the line is empty and prints the syntax error.
 * 
 * @param line user input 
 * @return boolean, true if it's a valid complete line, false other wise.
 */
bool		ms_line_iscomplete(char *line);

// Helper functions for split_with_no_quotes
char		*chrskip(char *s, char c);
int			split_with_no_quotes_len(char *line, int c);
int			*ms_char_positions(char *line, int c);

/**
 * @brief Splits a string by a character unless the character is inside quotes.
 * 
 * @param line the string to split
 * @param char to split by 
 * @return array of strings 
 */
char		**split_with_no_quotes(char *line, int c);

/**
 * @brief Edits the given to expand any env vars.
 * 
 * @param line user input
 * @return boolean, false on failure.
 */
void		ms_line_expand_vars(char **line, t_ms *shell);

// Helper for line_expand
int			get_next_index(char *line, char pos);

// Helper for line_expand
char		*value_at(char *line, int pos, t_ms *shell);

/**
 * @brief Counts how many pipes which is not contained inside quotations.
 * 
 * @param line user input
 * @return pipes count 
 */
size_t		ms_pipes_count(char *line);

/**
 * @brief checks and prints the errors
 * 
 * @param line_chunks
 * @return boolean
 */
bool		ms_chunks_iscomplete(char **chunks);

/**
 * @brief Tells if the given line has input.
 * 
 * @param line_chunk 
 * @return boolean
 */
bool		ms_contains_redirect(char *line_chunk, char type);

/**
 * @brief Reads the line for the input file name
 * 
 * @param line_chunk 
 * @return file_name (malloced string), or NULL if it doesn't exist.
*/
t_file		*ms_get_next_redirect(char **line_chunk, char type);

/**
 * @brief Tells if the given line has a command.
 * 
 * @param line_chunk 
 * @return boolean
 */
bool		ms_contains_cmd(char *line_chunk);

/**
 * @brief Reads the line for the cmd
 * 
 * @param line_chunk 
 * @return file_name (malloced string)
 */
char		*ms_get_cmd(char *line_chunk);

/**
 * @brief Reads the command string and checks if it's valid.
 * 
 * @param line_piece
 * @param chunk to be stored in 
 * @return Command arguments or NULL if not found
 */
char		**ms_get_fullcmd(char **line_piece);

/**
 * @brief Gets the command chunks from the divided line.
 * 	might contain invalid commands
 * 
 * @param line_pieces 
 * @param shell 
 * @return array of chunks
 */
t_cmd_chunk	**ms_command_chunks_get(char **line_pieces, size_t amount);

// error check/handle functions 
int			check_err(char *func_name, int ret_value);
int			ms_errno_check(char *err_header, int ret_value);
int			get_exit_status(int err);
void		exit_msg(char *head, char *err_msg, int err_code, t_alloced *mem);

// cleanup
void		ms_clean(t_cmd_chunk **chunks, char **str_chunks, char *line);

// builtins
int			get_builtin_no(char **cmd);
int			handle_builtins(t_ms *shell, int i, int builtin_no);
bool		exec_builtin_solo(t_ms *shell);

int			ms_echo(char **strs);
int			ms_pwd(void);
int			ms_cd(t_ms *shell, char **path, int arg_count);
int			ms_exit(char **args, int arg_count, t_ms *shell);
int			ms_env(t_ms *shell);
int			ms_export(t_ms *shell, char **args, int arg_count);
int			ms_unset(t_ms *shell, char **strs, int arg_count);

// execution controller function
int			ms_exec_cmds(t_ms *shell, int pipe_count);

// pipes 
int			ms_pipex(t_ms *shell, int cmd_count);
t_alloced	*ms_get_path(int p1[], int p2[], t_ms *shell, int i);
int			open_file(char *file_name, int open_flags);
int			is_regular_file(const char *path);
char		*get_pathname(char *cmd_name, char **envp);

void		redirect_input(t_cmd_chunk **chunks);
void		redirect_output(t_cmd_chunk **chunks);

void		ms_sigint_handler(int n);
void		ms_sigquit_handler(int sig);
void		ms_child_sigint_handler(int sig);
void		ms_hdoc_sigint_handler(int sig);
int			ms_get_sig_status(int sig_no);
void		ms_clean(t_cmd_chunk **chunks, char **string_chunks, char *line);

#endif
