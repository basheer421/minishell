/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:28:48 by bammar            #+#    #+#             */
/*   Updated: 2023/01/06 23:00:44 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_builtins(char *line, t_ms *shell)
{
	char **strs;

	strs = ft_split(line, ' ');
	if (strs && strs[0])
	{
		if (ft_strncmp(strs[0], "echo", 5) == 0)
		{
			if (strs[1] && ft_strncmp(strs[1], "-n", 3) == 0) // -n flag is set to true
				ms_echo(strs, 1);
			else
				ms_echo(strs, 0);
		}
		else if (ft_strncmp(strs[0], "pwd", 4) == 0)
			ms_pwd(shell);
		else if (ft_strncmp(strs[0], "exit", 5) == 0)
		{
			free(line);
			ft_split_destroy(strs);
			ms_exit(0, shell);
		}	
		ft_split_destroy(strs);
	}
}

int	ms_line_read(const char *prompt, t_ms *shell)
{
	char	*line;
	char	**string_chunks;
	t_command_chunk	**chunks;

	line = readline(prompt);
	if (!line || !*line)
		return (free(line), 1);
	shell->error_code = ms_error_invalid_char(line);
	if (shell->error_code != 0)
		return (free(line), shell->error_code);
	add_history(line);
	check_builtins(line, shell);
	if (ms_line_isempty(line))
		return (free(line), 0);
	if (ms_pipes_count(line) == 0)
		return (0); // should be "return a function that does one command"
	string_chunks = ms_pipes_divide(line);
	if (!string_chunks)
		return (free(line), 1);
	// use pipex with the given chunks
	chunks = ms_command_chunks_get(string_chunks, ms_pipes_count(line) + 1);
	if (!chunks)
		return (0);
	return (ft_split_destroy(string_chunks), free(line), 0);
}
