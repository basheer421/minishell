/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:28:48 by bammar            #+#    #+#             */
/*   Updated: 2023/01/04 22:58:54 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_line_read(const char *prompt, t_ms *shell)
{
	char	*line;
	char	**chunks;

	line = readline(prompt);
	if (!line || !*line)
		return (free(line), 1);
	shell->error_code = ms_error_invalid_char(line);
	if (shell->error_code != 0)
		return (free(line), shell->error_code);
	add_history(line);
	if (ms_line_isempty(line))
		return (free(line), 0);
	if (ms_pipes_count(line) == 0)
		return (0); // should be "return a function that does one command"
	chunks = ms_pipes_divide(line);
	if (!chunks)
		return (free(line), 1);
	// use pipex with the given chunks
	return (ft_split_destroy(chunks), free(line), 0);
}
