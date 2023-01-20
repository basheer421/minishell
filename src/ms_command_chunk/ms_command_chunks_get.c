/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_chunks_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:04:34 by bammar            #+#    #+#             */
/*   Updated: 2023/01/20 18:39:09 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd_chunk	**chunk_init(size_t amount)
{
	t_cmd_chunk	**chunks;
	size_t			i;

	chunks = malloc(sizeof(t_cmd_chunk *) * (amount + 1));
	if (!chunks)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		chunks[i] = ft_calloc(1, sizeof(t_cmd_chunk));
		chunks[i]->input_fd = -2;
		chunks[i]->output_fd = 1;
		if (!chunks[i])
			return (NULL);
		i++;
	}
	chunks[i] = NULL;
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

t_cmd_chunk	**ms_command_chunks_get(char **line_pieces,
										size_t amount)
{
	t_cmd_chunk	**chunks;
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
