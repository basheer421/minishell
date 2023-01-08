/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_chunks_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:04:34 by bammar            #+#    #+#             */
/*   Updated: 2023/01/08 13:26:15 by bammar           ###   ########.fr       */
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
		chunks[i]->input_fd = -2;
		chunks[i]->output_fd = 1;
		if (!chunks[i])
			return (NULL);
		i++;
	}
	return (chunks);
}

// 0 means the next part is input, 1 means output and 2 means it's a command
static int	token_type(char *line)
{
	if (!*ft_skip_spaces(line))
		return (3);
	if (ms_contains_input(line))
		return (0);
	if (ms_contains_output(line))
		return (1);
	if (ms_contains_cmd(line))
		return (2);
	return (-1);
}

t_command_chunk	**ms_command_chunks_get(char **line_pieces,
										size_t amount)
{
	t_command_chunk	**chunks;
	size_t			i;
	int				token;

	chunks = chunk_init(amount);
	if (!chunks)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		token = token_type(line_pieces[i]);
		if (token == 0)
			chunks[i]->input_fd = ms_get_input_fd(line_pieces[i], chunks[i]);
		// else if (token == 1)
		// 	chunks[i]->output_fd = ms_get_output_fd(line_pieces[i], chunks[i]);
		else if (token == 2)
			chunks[i]->cmd = ms_get_fullcmd(line_pieces[i], chunks[i]);
		else if (token == 3)
			return (NULL); // ERROR
		i++;
	}
	return (chunks);
}
