/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_chunks_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:04:34 by bammar            #+#    #+#             */
/*   Updated: 2023/02/12 21:24:49 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd_chunk	**chunk_init(size_t amount)
{
	t_cmd_chunk	**chunks;
	size_t		i;

	chunks = ft_malloc(sizeof(t_cmd_chunk *) * (amount + 1));
	i = 0;
	while (i < amount)
	{
		chunks[i] = ft_calloc(1, sizeof(t_cmd_chunk));
		if (!chunks[i])
			exit(EXIT_FAILURE);
		chunks[i]->inputs = ft_lstnew(NULL);
		chunks[i]->outputs = ft_lstnew(NULL);
		i++;
	}
	chunks[i] = NULL;
	return (chunks);
}

// 60 means the next part is input, 62 means output and 2 means it's a command
static int	token_type(char *line)
{
	if (ms_contains_redirect(line, '<'))
		return ('<');
	if (ms_contains_redirect(line, '>'))
		return ('>');
	if (ms_contains_cmd(line))
		return (2);
	return (-1);
}

static bool	is_err(t_cmd_chunk **chunks, int reach, char *line)
{
	char	*nline;

	nline = ft_strtrim(line, " ");
	if (!chunks[reach]->cmd && !chunks[reach]->inputs->content
		&& !chunks[reach]->outputs->content)
		return (free(nline), true);
	return (free(nline), false);
}

static bool	add_back(t_cmd_chunk *chunk, char type, t_file *new_node)
{
	t_list	*temp;
	t_list	**lst;

	if (!new_node)
		return (false);
	lst = NULL;
	if (type == '>')
		lst = &(chunk->outputs);
	else if (type == '<')
		lst = &(chunk->inputs);
	ft_lstadd_back(lst, ft_lstnew(new_node));
	if ((*lst)->content == NULL)
	{
		temp = (*lst);
		(*lst) = (*lst)->next;
		free(temp);
	}
	return (true);
}

t_cmd_chunk	**ms_command_chunks_get(char **line_pieces,
									size_t amount)
{
	t_cmd_chunk	**chunks;
	int			i;
	int			token;
	int			ptr;

	chunks = chunk_init(amount);
	i = -1;
	while (++i < (int)amount)
	{
		ptr = 0;
		while (line_pieces[i][ptr] && *ft_skip_spaces(&line_pieces[i][ptr]))
		{
			token = token_type(&line_pieces[i][ptr]);
			if (token == -1 && is_err(chunks, i, &line_pieces[i][ptr]))
				return (ms_clean(chunks, NULL, NULL), NULL);
			else if (token == 2)
				chunks[i]->cmd = ms_get_fullcmd(line_pieces[i], &ptr);
			else if (token == '<' || token == '>')
				if (!add_back(chunks[i], token,
						ms_get_next_redirect(line_pieces[i], token, &ptr)))
					return (ms_clean(chunks, NULL, NULL), NULL);
		}
	}
	return (chunks);
}
