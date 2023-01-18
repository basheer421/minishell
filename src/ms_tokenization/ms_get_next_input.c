/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_next_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:17:25 by bammar            #+#    #+#             */
/*   Updated: 2023/01/18 18:05:09 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make sure to handle the quotes, never handle double quotes
// 	handle double quotes after variables handling and 
//	change them to double quotes if no env vars are inside them
//	also make sure to join all quotes if no spaces are between them
//	(comments for basheer so e doesn't forget xd)
char	*ms_get_next_input(char *line_chunk)
{
	char	*name;
	int		i;
	int		len;

	line_chunk = ft_skip_spaces(line_chunk);
	if (!line_chunk || *line_chunk != '<')
		return (NULL);
	line_chunk = ft_skip_spaces(line_chunk + 1);
	line_chunk += *line_chunk == '\'';
	len = 0;
	while (line_chunk[len]
		&& !ft_is_space(line_chunk[len]) && line_chunk[len] != '<'
		&& line_chunk[len] != '>' && line_chunk[len] != '\'')
		len++;
	name = ft_malloc(len + 1);
	i = -1;
	while (++i < len)
		name[i] = line_chunk[i];
	line_chunk +=  len;
	return (name);
}
