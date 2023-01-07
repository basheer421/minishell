/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes_divide.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:34:19 by bammar            #+#    #+#             */
/*   Updated: 2022/12/28 16:13:43 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_length(char *line, int current_index, int position)
{
	if (position == -1)
		return (ft_strlen(line) - current_index);
	return (position - current_index);
}

char	**ms_pipes_divide(char *line)
{
	char	**content;
	int		current_index;
	int		*positions;
	size_t	i;
	size_t	content_size;

	content_size = ms_pipes_count(line) + 1;
	positions = ms_pipes_positions(line);
	if (!positions)
		return (NULL);
	content = malloc(sizeof(char *) * (content_size + 1));
	if (!content)
		return (NULL);
	i = 0;
	current_index = 0;
	while (i < content_size)
	{
		content[i] = ft_substr(line, current_index,
				get_length(line, current_index, positions[i]));
		if (!content[i])
			return (free(positions), free(content), NULL);
		current_index = positions[i++] + 1;
	}
	content[i] = NULL;
	return (free(positions), content);
}
