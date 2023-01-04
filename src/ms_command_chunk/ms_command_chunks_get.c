/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_chunks_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:04:34 by bammar            #+#    #+#             */
/*   Updated: 2023/01/04 22:58:20 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*input;
	int		in_fd;

	chunks = chunk_init(line_pieces, amount);
	if (!chunks)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		while (*line_pieces[i])
		{
			while (ms_contains_input(*line_pieces[i]))
			{
				input = ms_get_next_input(*line_pieces[i]);
				if (access(input, F_OK) != 0)
					return (NULL); // WRONG FILE NAME
				in_fd = open(input, O_RDONLY);
				if (in_fd < 0)
					return (NULL);
				chunks[i]->input_fd = in_fd;
			}
		}
		i++;
	}

}
