/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:30:21 by bammar            #+#    #+#             */
/*   Updated: 2023/01/02 16:23:23 by bammar           ###   ########.fr       */
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
}				t_ms;

/**
 * @brief This is a command chunk, should be like this
 * {{ "< input cmd  >  output" }}, Note: input should be the LIMITER incase
 * "input_isheredoc" is true.
 * Also, "input" can be NULL, and if "output" is NULL
 * 	then the default is "stdout {fd = 1}".
 * 
 */
typedef struct s_command_chunk
{
	char		*cmd;
	bool		input_isheredoc;
	bool		append_to_output;
	char		*input;
	char		*output;
}				t_command_chunk;

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

/**
 * @brief Tells if the line has at least one command.
 * 
 * @param line user input
 * @return boolean
 */
bool			ms_line_contains_commands(char *line, t_ms *shell);

/**
 * @brief Execute the valid commands in parallel as
 *  "minishell" requires only that.
 * 
 * @param line user input
 * @return 0 on success or error code
 */
int				ms_line_execute_commands(char *line);

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
 * @brief Gets the command chunks from the divided line.
 * 	might contain invalid commands
 * 
 * @param line_pieces 
 * @param shell 
 * @return array of chunks
 */
t_command_chunk	**ms_command_chunks_get(char **line_pieces, size_t amount);

/**
 * @brief Executes a command chunk.
 * Make sure everything is done in new temporary shell.
 * 
 * @param command_chunk 
 * @return {int} Error code
 */
int				ms_command_chunk_execute(t_command_chunk *command_chunk,
					t_ms *shell);

/**
 * @brief Changes the behavior of this program when receiving signals.
 * 
 * @param sig The received signal.
 */
void			ms_signal(void);

#endif
