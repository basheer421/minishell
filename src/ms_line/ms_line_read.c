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
	size_t			pipe_count;
	t_cmd_chunk		**chunks;

	printf("new prompt!!!!\n");
	line = readline(prompt);
	if (!line)
		ms_exit(NULL, 1, shell);
	if (ms_line_isempty(ft_skip_spaces(line)))
		return (free(line), 0);
	add_history(line);
	if (!ms_line_iscomplete(line))
		return (ms_clean(NULL, NULL, line), 1);
	ms_line_expand_vars(&line, shell);
	if (ms_line_isempty(ft_skip_spaces(line)))
		return (free(line), 0);
	string_chunks = split_with_no_quotes(line, '|');
	if (!string_chunks)
		return (ms_clean(NULL, NULL, line), 1);
	pipe_count = ms_pipes_count(line);
	chunks = ms_command_chunks_get(string_chunks, pipe_count + 1);
	if (!chunks)
		return (ms_clean(chunks, string_chunks, line), 0);
	ms_clean(NULL, string_chunks, line);
	return (ms_exec_cmds(chunks, pipe_count, shell));
}
