/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:28:48 by bammar            #+#    #+#             */
/*   Updated: 2023/01/08 14:38:32 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_line_read(const char *prompt, t_ms *shell)
{
	char			*line;
	char			**string_chunks;
	t_command_chunk	**chunks;

	line = readline(prompt);
	if (!line || !*line)
		return (free(line), 1);
	if (shell->error_code != 0)
		return (free(line), shell->error_code);
	add_history(line);
	shell->error_code = ms_error_invalid_char(line);
	if (ms_line_isempty(line) || shell->error_code == 127)
		return (free(line), 0);
	ms_line_expand_vars(&line, shell);
	string_chunks = ms_pipes_divide(line);
	if (!string_chunks)
		return (free(line), 1);
	// use pipex with the given chunks
	chunks = ms_command_chunks_get(string_chunks, ms_pipes_count(line) + 1);
	if (!chunks)
		return (0);
	
	int i;
	i = -1;
	while (chunks[++i] != NULL)
		handle_builtins(chunks[i]->cmd, shell);
	return (ft_split_destroy(string_chunks), free(line), 0);
}
