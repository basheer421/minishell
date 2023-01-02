/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:28:48 by bammar            #+#    #+#             */
/*   Updated: 2023/01/02 21:46:37 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// not done
int	ms_line_read(const char *prompt, t_ms *shell)
{
	char	*line;

	line = readline(prompt);
	if (!line || !*line)
		return (free(line), 1);
	shell->error_code = ms_invalid_char(line);
	if (shell->error_code != 0)
		return (free(line), shell->error_code);
	add_history(line);
	if (!ms_line_contains_commands(line, shell))
		exit(1);
	// chunks = ms_pipes_divide(line);
	// if (!chunks)
	// 	return (free(line), 1);
	// ft_split_destroy(chunks);
	return (free(line), 0);
}
