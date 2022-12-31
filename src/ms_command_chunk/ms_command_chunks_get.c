/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_chunks_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:04:34 by bammar            #+#    #+#             */
/*   Updated: 2022/12/31 18:07:39 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_inputs(char *line_segment);

static char	*get_cmd(char *line_segment);

static t_list	*get_outputs(char *line_segment);


static t_command_chunk	**chunk_init(char **line_pieces,
									size_t amount)
{
	t_command_chunk	**chunks;
	size_t			i;

	chunks = malloc(sizeof(t_command_chunk *) * amount);
	if (!chunks)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		chunks[i] = ft_calloc(1, sizeof(t_command_chunk));
		if (!chunks[i])
			return (NULL);
		i++;
	}
	return (chunks);
}

t_command_chunk	**ms_command_chunks_get(char **line_pieces,
										size_t amount)
{
	t_command_chunk **chunks;
	size_t i;

	chunks = chunk_init(line_pieces, amount);
	if (!chunks)
		return (NULL);
}
