/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_chunks_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:04:34 by bammar            #+#    #+#             */
/*   Updated: 2023/01/06 23:02:06 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command_chunk	**chunk_init(size_t amount)
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
	size_t 			i;

	chunks = chunk_init(amount);
	if (!chunks)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		chunks[i]->input_fd = ms_get_input_fd(&line_pieces[i],
			chunks[i]);
		if (chunks[i]->input_fd == -1)
			; // FILE NOT FOUND ERROR
		else if (chunks[i]->input_fd != -2)
			ft_putendl_fd("hello world", chunks[i]->input_fd);
		i++;
	}
	return (chunks);
}
