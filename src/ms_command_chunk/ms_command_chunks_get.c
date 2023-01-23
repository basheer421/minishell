/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_chunks_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:04:34 by bammar            #+#    #+#             */
/*   Updated: 2023/01/21 15:42:10 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command_chunk	**chunk_init(size_t amount)
{
	t_command_chunk	**chunks;
	size_t			i;

	chunks = ft_malloc(sizeof(t_command_chunk *) * (amount + 1));
	i = 0;
	while (i < amount)
	{
		chunks[i] = ft_calloc(1, sizeof(t_command_chunk));
		if (!chunks[i])
			return (NULL);
		chunks[i]->input_fd = 0;
		chunks[i]->output_fd = 1;
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

static bool is_err(t_command_chunk *chunk)
{
	if (chunk->input_fd != -1 && !chunk->output_fd != -1
		&& !chunk->cmd)
		return (true); // command not found
	if (chunk->input_fd == -1)
	{
		return (true); // No such file or directory
	}
	if (chunk->output_fd == -1)
		return (true); // some weird err lol
	return (false);
}

t_command_chunk	**ms_command_chunks_get(char **line_pieces,
										size_t amount)
{
	t_command_chunk	**chunks;
	int				i;
	int				token;
	char			*string_head;

	chunks = chunk_init(amount);
	i = -1;
	while (++i < (int)amount)
	{
		string_head = line_pieces[i];
		token = token_type(line_pieces[i]);
		if (token == 0)
			chunks[i]->input_fd = ms_get_input_fd(line_pieces[i], chunks[i]);
		else if (token == 1)
			chunks[i]->output_fd = ms_get_output_fd(line_pieces[i], chunks[i]);
		if (token == 2)
			chunks[i]->cmd = ms_get_fullcmd(line_pieces[i], chunks[i]);
		line_pieces[i] = string_head;
		if (token == -1 && is_err(chunks[i]))
			return (NULL); // ERRORS
	}
	return (chunks);
}
