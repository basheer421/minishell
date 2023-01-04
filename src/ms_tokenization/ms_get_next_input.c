/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_next_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:17:25 by bammar            #+#    #+#             */
/*   Updated: 2023/01/04 22:59:43 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_next_input(char *line_chunk)
{
	char	*name;
	int		i;
	int		len;

	line_chunk = ft_skip_spaces(line_chunk);
	if (!line_chunk || *line_chunk != '<')
		return (NULL);
	line_chunk = ft_skip_spaces(line_chunk + 1);
	len = 0;
	while (line_chunk[len]
		&& !ft_is_space(line_chunk[len]) && line_chunk[len] != '<'
		&& line_chunk[len] != '>')
		len++;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	i = -1;
	while (++i < len)
		name[i] = line_chunk[i];
	line_chunk +=  len;
	return (name);
}
