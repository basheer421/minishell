/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:28:48 by bammar            #+#    #+#             */
/*   Updated: 2022/12/25 16:40:29 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reads the command line and returns the output
char	*ms_line_read(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
		return (NULL);
	return (line);
}
