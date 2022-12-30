/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:28:48 by bammar            #+#    #+#             */
/*   Updated: 2022/12/30 15:24:27 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// not done
int	ms_line_read(const char *prompt, t_ms *shell)
{
	char	*line;
	// char	**chunks;

	line = readline(prompt);
	if (line && *line)
	{
		add_history(line);
		if (!ms_line_contains_commands(line, shell))
			return (free(line), 1);
		// chunks = ms_pipes_divide(line);
		// if (!chunks)
		// 	return (free(line), 1);
		// ft_split_destroy(chunks);
	}
	return (free(line), 0);
}
