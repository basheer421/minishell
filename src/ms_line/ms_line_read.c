/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:28:48 by bammar            #+#    #+#             */
/*   Updated: 2022/12/26 15:33:41 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_line_read(const char *prompt)
{
	char	*line;

	while (1)
	{
		line = readline(prompt);
		if (line && *line)
		{
			add_history(line);
			if (ms_line_contains_commands(line))
				break ;
		}
	}
	return (free(line), 0);
}
