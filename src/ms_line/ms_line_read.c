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

static int	line_init(char **line, t_ms *shell)
{
	if (**line)
		add_history(*line);
	if (ms_line_isempty(ft_skip_spaces(*line)))
		return (ms_clean(NULL, NULL, *line), 0);
	ms_add_spaces(line);
	if (!ms_line_iscomplete(*line))
		return (ms_clean(NULL, NULL, *line), 0);
	ms_line_expand_vars(line, shell);
	if (ms_line_isempty(ft_skip_spaces(*line)))
		return (ms_clean(NULL, NULL, *line), 0);
	return (1);
}

int	ms_line_read(const char *prompt, t_ms *shell)
{
	char			*line;
	char			**string_chunks;
	size_t			pipe_count;

	line = readline(prompt);
	if (!line)
		ms_exit(NULL, 1, shell);
	if (!line_init(&line, shell))
		return (0);
	string_chunks = split_with_no_quotes(line, '|');
	if (!string_chunks)
		return (ms_clean(NULL, NULL, line), 1);
	pipe_count = ms_pipes_count(line);
	shell->cur_cmd = ms_command_chunks_get(string_chunks, pipe_count + 1);
	if (!shell->cur_cmd)
		return (ms_clean(shell->cur_cmd, string_chunks, line), 0);
	return (ms_clean(NULL, string_chunks, line),
		ms_exec_cmds(shell, pipe_count));
}
