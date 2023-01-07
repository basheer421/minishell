/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_next_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:44:33 by bammar            #+#    #+#             */
/*   Updated: 2023/01/04 22:25:30 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_next_output(char *line_chunk)
{
	char	*name;
	char	*line;
	int		i;
	int		len;

	if (ms_contains_input(line_chunk))
		return (NULL);
	line = ft_skip_spaces(line_chunk);
	if (!line || *line != '>')
		return (NULL);
	line = ft_skip_spaces(line + 1);
	len = 0;
	while (line[len] && !ft_is_space(line[len]))
		len++;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	i = -1;
	while (++i < len)
		name[i] = line[i];
	return (name);
}
