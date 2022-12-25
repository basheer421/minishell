/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:28:48 by bammar            #+#    #+#             */
/*   Updated: 2022/12/25 20:21:46 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reads the command line and returns the output
int	ms_line_read(const char *prompt)
{
	char	*line;

	while (1)
	{
		line = readline(prompt);
		if (line && *line)
    	{
			add_history(line);
			// if (ms_line_containscommands(line))
			// 	ms_line_excute_commands(line);
		}
		
	}
	return (free(line), 0);
}
