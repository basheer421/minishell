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

// only for testing, remove later
// static	void	show_chunks(t_cmd_chunk **chunks)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (chunks[++i])
// 	{
// 		printf("chunk %d\n", i);
// 		j = -1;
// 		while (chunks[i]->cmd[++j] != NULL)
// 			printf("cmds:%s\n", chunks[i]->cmd[j]);
// 	}
// }

int	ms_line_read(const char *prompt, t_ms *shell)
{
	char			*line;
	char			**string_chunks;
	size_t			pipe_count;
	bool			cmd_is_builtin;
	t_cmd_chunk		**chunks;

	line = readline(prompt);
	if (!line)
		ms_exit(NULL, 0, shell);
	if (ms_line_isempty(line))
		return (free(line), 0);
	add_history(line);
	ms_line_expand_vars(&line, shell);
	string_chunks = ms_pipes_divide(line);
	if (!string_chunks)
		return (free(line), 1);
	pipe_count = ms_pipes_count(line);
	chunks = ms_command_chunks_get(string_chunks, pipe_count + 1);
	if (!chunks)
		return (ft_split_destroy(string_chunks), 0);
	cmd_is_builtin = false;
	if (pipe_count == 0)
		cmd_is_builtin = handle_builtins(chunks[0]->cmd, shell);
	if (pipe_count > 0 || !cmd_is_builtin)
		g_exit_status = pipex(chunks, pipe_count + 1, shell);
	return (ms_clean(chunks, string_chunks, line), 0);
}
