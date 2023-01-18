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
// static	void	show_chunks(t_command_chunk **chunks)
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
	int				i;
	t_command_chunk	**chunks;

	line = readline(prompt);
	if (!line || !*line)
		return (free(line), 0);
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
	printf("working\n");
	// show_chunks(chunks);
	i = -1;
	while (chunks[++i] != NULL)
		handle_builtins(chunks[i]->cmd, shell);
	return (ft_split_destroy(string_chunks), free(line), 0);
}
