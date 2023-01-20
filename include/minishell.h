/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:30:21 by bammar            #+#    #+#             */
/*   Updated: 2023/01/20 18:12:49 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ht.h"
# include "libft.h"
# include "pipex.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/param.h>


/**
 * @brief Stores a hash map of environment variables,
 *  and stores the current dir.
 * 	Note that current_dir is malloced and should be freed.
 *
 */
typedef struct s_ms
{
	t_ht		*env_vars;
	char		*current_dir;
	bool		is_interactive_mode;
	int			error_code;
}				t_ms;

/**
 * @brief This is a command chunk, should be like this
 * {{ "< input cmd  >  output" }}, Note: input should be the LIMITER incase
 * "input_isheredoc" is true.
 * 
 */
typedef struct s_command_chunk
{
	char		**cmd;
	bool		input_isheredoc;
	bool		append_to_output;
	int			input_fd;
	int			output_fd;
}				t_command_chunk;

/**
 * @brief Detect if "\" or ";" is found.
 * 
 * @param line user input
 * @return int error code or 0
 */
int				ms_error_invalid_char(char *line);

/**
 * @brief Reads the environment variables and stores them inside a struct.
 * 	Also gets the current working dir
 * 
 * @param envp enviroment variables from main() fucntion
 * @return mini shell struct pointer (t_ms *)
 */
t_ms			*ms_init(char **envp);

/**
 * @brief Destroys and frees everything inside the given shell (t_ms).
 * 
 * @param shell 
 */
void			ms_destroy(t_ms *shell);

/**
 * @brief Reads the command line and does the main functions,
 * 		which are catching signels and executing commands.
 * 
 * @param prompt desired prompt
 * @return Error code
 */
int				ms_line_read(const char *prompt, t_ms *shell);

// Helper functions for split_with_no_quotes
char			*chrskip(char *s, char c);
int				split_with_no_quotes_len(char *line, int c);
int				*ms_char_positions(char *line, int c);

/**
 * @brief Splits a string by a character unless the character is inside quotes.
 * 
 * @param line the string to split
 * @param char to split by 
 * @return array of strings 
 */
char			**split_with_no_quotes(char *line, int c);

/**
 * @brief Tells if the line is empty.
 * 
 * @param line user input
 * @return boolean, true if it's empty.
 */
bool			ms_line_isempty(char *line);

// /**
//  * @brief Tells if the line has at least one command.
//  * 
//  * @param line user input
//  * @return boolean
//  */
// bool			ms_line_contains_commands(char *line, t_ms *shell);

/**
 * @brief Edits the given to expand any env vars.
 * 
 * @param line user input
 * @return boolean, false on failure.
 */
void			ms_line_expand_vars(char **line, t_ms *shell);
int				get_next_index(char *line, char pos);
char			*value_at(char *line, int pos, t_ms *shell);

/**
 * @brief Execute the valid commands in parallel as
 *  "minishell" requires only that.
 * 
 * @param line user input
 * @return 0 on success or error code
 */
// int				ms_line_execute_commands(char *line);
// idk, u handle this

/**
 * @brief Gets the positions of pipes to make it easier
 * 	when dividing the contents.
 * 
 * @param line user input
 * @return int* pipes positions, ends with (-1) for termination
 */
int				*ms_pipes_positions(char *line);

/**
 * @brief Counts how many pipes which is not contained inside quotations.
 * 
 * @param line user input
 * @return pipes count 
 */
size_t			ms_pipes_count(char *line);

/**
 * @brief Divides contents between pipes to a 2d array.
 * 	needs a check after.
 * 
 * @param line user input
 * @return 2d array contents (might be commands)
 */
char			**ms_pipes_divide(char *line);

/**
 * @brief Tells if the given line has input.
 * 
 * @param line_chunk 
 * @return boolean
 */
bool			ms_contains_input(char *line_chunk);

/**
 * @brief Reads the line for the input file name
 * 
 * @param line_chunk 
 * @return file_name (malloced string), or NULL if it doesn't exist.
 */
char			*ms_get_next_input(char *line_chunk);

/**
 * @brief Using get_next_input() we get the last fd,
 * 	and store it inside "chunk"
 * 
 * @param line_piece
 * @param chunk to be stored in
 * @return int fd, or -1 on error
 */
int				ms_get_input_fd(char *line_piece,
				t_command_chunk *chunk);

/**
 * @brief Tells if the given line has a command.
 * 
 * @param line_chunk 
 * @return boolean
 */
bool			ms_contains_cmd(char *line_chunk);

/**
 * @brief Reads the line for the cmd
 * 
 * @param line_chunk 
 * @return file_name (malloced string)
 */
char			*ms_get_cmd(char *line_chunk);

/**
 * @brief Reads the command string and checks if it's valid.
 * 
 * @param line_piece
 * @param chunk to be stored in 
 * @return Command arguments or NULL if not found
 */
char			**ms_get_fullcmd(char *line_piece,
				t_command_chunk *chunk);

/**
 * @brief Tells if the given line has output.
 * 
 * @param line_chunk 
 * @return boolean
 */
bool			ms_contains_output(char *line_chunk);

/**
 * @brief Reads the line for the output file name
 * 
 * @param line_chunk 
 * @return file_name (malloced string)
 */
char			*ms_get_next_output(char *line_chunk);

/**
 * @brief Gets the command chunks from the divided line.
 * 	might contain invalid commands
 * 
 * @param line_pieces 
 * @param shell 
 * @return array of chunks
 */
t_command_chunk	**ms_command_chunks_get(char **line_pieces, size_t amount);

// /**
//  * @brief Executes a command chunk.
//  * Make sure everything is done in new temporary shell.
//  * 
//  * @param command_chunk 
//  * @return {int} Error code
//  */
// int				ms_command_chunk_execute(t_command_chunk *command_chunk,
// 					t_ms *shell);

/**
 * @brief Checks if a function returned an error and if so displays appropriate error message
 * 
 * @param err_header Name of the function being called, to be used in error message
 * @param ret_value Return value of the function called 
 * @return ret_value
 */
int		ms_errno_check(char *err_header, int ret_value);
void	ms_clean(t_command_chunk **chunks, char **string_chunks, char *line);
// void	handle_builtins(char **strs, t_ms *shell);
int	handle_builtins(char *cmd_str, t_ms *shell);

/**
 * @brief Runs the echo command on the given strings
 * 
 * @param strs array of strings to be output on the screen
 * @param n_flag if set to true echo will not output a trailing newline
 */
void			ms_echo(char **strs, bool n_flag);
void			ms_pwd(void);
void			ms_cd(t_ms *shell, char **path, int arg_count);
int				ms_exit(char **args, int arg_count, t_ms *shell);
void			ms_env(t_ms *shell);
void			ms_export(t_ms *shell, char **args, int arg_count);
void			ms_unset(t_ms *shell, char **strs, int arg_count);

/**
 * @brief Executes a command chunk.
 * Make sure everything is done in new temporary shell.
 * 
 * @param command_chunk 
 * @return {int} Error code
 */
int				ms_command_chunk_execute(t_command_chunk *command_chunk,
					t_ms *shell);
int				pipex(char **cmd_strs, int cmd_count, t_ms *shell);
t_alloced		*set_alloc(int p1[], int p2[], t_ms *shell);
t_alloced		*check_cmd_path(int p1[], int p2[], char *cmd_str, t_ms *shell);
int				exec_cmd(int p1[], int p2[], char *cmd_str, t_ms *shell);

#endif
