/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_chunks_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:04:34 by bammar            #+#    #+#             */
/*   Updated: 2022/12/29 21:21:29 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command_chunk	**chunk_init(char **line_pieces,
									t_ms *shell,
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
										t_ms *shell,
										size_t amount)
{
	t_command_chunk **chunks;
	size_t i;

	chunks = chunk_init(line_pieces, shell, amount);
	if (!chunks)
		return (NULL);
}