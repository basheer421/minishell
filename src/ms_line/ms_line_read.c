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

static void	check_builtins(t_command_chunk *chunk, t_ms *shell)
{
	if (ft_strncmp(chunk->cmd[0], "echo", 5) == 0)
	{
		if (chunk->cmd[1] && ft_strncmp(chunk->cmd[1], "-n", 3) == 0) // -n flag is set to true
			ms_echo(chunk->cmd, 1);
		else
			ms_echo(chunk->cmd, 0);
	}
	else if (ft_strncmp(chunk->cmd[0], "pwd", 4) == 0)
		ms_pwd(shell);
	else if (ft_strncmp(chunk->cmd[0], "exit", 5) == 0)
	{
		ft_split_destroy(chunk->cmd);
		ms_exit(0, shell);
	}	
	ft_split_destroy(chunk->cmd);
}

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
	string_chunks = ms_pipes_divide(line);
	if (!string_chunks)
		return (free(line), 1);
	// if (!ms_line_expand_vars(string_chunks, shell))
	// 	return (0);
	// use pipex with the given chunks
	chunks = ms_command_chunks_get(string_chunks, ms_pipes_count(line) + 1);
	if (!chunks)
		return (0);
	int i = -1;
	while (chunks[0]->cmd[++i] != NULL)
		printf("cmds:%s\n", chunks[0]->cmd[i]);
	i = -1;
	while (chunks[++i] != NULL)
		check_builtins(chunks[i], shell);	
	return (ft_split_destroy(string_chunks), free(line), 0);
}
