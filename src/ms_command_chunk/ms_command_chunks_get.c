/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_chunks_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 21:04:34 by bammar            #+#    #+#             */
/*   Updated: 2023/01/25 02:17:53 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd_chunk	**chunk_init(size_t amount)
{
	t_cmd_chunk	**chunks;
	size_t			i;

	chunks = ft_malloc(sizeof(t_cmd_chunk *) * (amount + 1));
	i = 0;
	while (i < amount)
	{
		chunks[i] = ft_calloc(1, sizeof(t_cmd_chunk));
		chunks[i]->inputs = ft_lstnew(NULL);
		chunks[i]->outputs = ft_lstnew(NULL);
		if (!chunks[i])
			exit(EXIT_FAILURE);
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

static bool	is_err(t_cmd_chunk **chunks, int reach)
{
	if (!chunks[reach]->cmd
		&& !chunks[reach]->inputs->content
		&& !chunks[reach]->outputs->content)
		return (true);
	return (false);
}

// static t_cmd_chunk	**adjust_redirects(t_cmd_chunk **chunks,
// 						int size)
// {
// 	int		i;
// 	t_list	*temp;

// 	i = -1;
// 	while (++i < size)
// 	{
// 		if (chunks[i]->inputs->next != NULL)
// 		{
// 			temp = chunks[i]->inputs;
// 			chunks[i]->inputs = chunks[i]->inputs->next;
// 			free(temp);
// 		}
// 		if (chunks[i]->outputs->next != NULL)
// 		{
// 			temp = chunks[i]->outputs;
// 			chunks[i]->outputs = chunks[i]->outputs->next;
// 			free(temp);
// 		}
// 	}
// }

static void	add_back(t_list **lst, t_list *new_node)
{
	t_list	*temp;

	if ((*lst)->content == NULL)
	{
		temp = (*lst);
		(*lst) = (*lst)->next;
		free(temp);
	}
	ft_lstadd_back(lst, new_node);
}

t_cmd_chunk	**ms_command_chunks_get(char **line_pieces,
										size_t amount)
{
	t_cmd_chunk		**chunks;
	int				i;
	int				token;
	char			*string_head;

	chunks = chunk_init(amount);
	i = -1;
	while (++i < (int)amount)
	{
		string_head = line_pieces[i];
		while (string_head && *ft_skip_spaces(string_head))
		{
			token = token_type(string_head);
			if (token == '<' || token == '>')
				add_back(&(chunks[i]->inputs),
					ft_lstnew(ms_get_next_redirect(&string_head, token)));
			else if (token == 2)
				chunks[i]->cmd = ms_get_fullcmd(&string_head);
			else if (token == -1 && is_err(chunks, i))
				return (NULL);
		}
	}
	return (chunks);
}
