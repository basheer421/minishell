/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_next_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:17:25 by bammar            #+#    #+#             */
/*   Updated: 2023/01/26 22:14:05 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_inside
{
	bool	quotes;
	bool	dquotes;
}			t_inside;


static int	end_pos(char *str, t_inside *inside)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((ft_is_space(str[i]) || str[i] == '>' || str[i] == '<')
			&& !inside->dquotes && !inside->quotes)
			return (i);
		else if (str[i] == '\'' && !inside->dquotes)
			inside->quotes = !inside->quotes;
		else if (str[i] == '\"' && !inside->quotes)
			inside->dquotes = !inside->dquotes;
	}
	return (i);
}

// static void report_unexpected_token(char next_c)
// {
// }

t_file	*ms_get_next_redirect(char **line_chunk, char type)
{
	int			len;
	t_inside	inside;
	t_file		*file;
	char		*temp;

	ft_bzero(&inside, sizeof(inside));
	file = ft_malloc(sizeof(t_file));
	*line_chunk = ft_skip_spaces(ft_skip_spaces(*line_chunk) + 1);
	file->is_extra = **line_chunk == type;
	*line_chunk += file->is_extra;
	*line_chunk = ft_skip_spaces(*line_chunk);
	len = end_pos(*line_chunk, &inside);
	if (len == 0)
		return (NULL); // unexpected token error
	*line_chunk += inside.dquotes || inside.quotes;
	file->name = ft_substr(file->name, 0, len);
	temp = file->name;
	file->name = ft_exclude_quotes(file->name);
	*line_chunk += len + (inside.dquotes || inside.quotes);
	return (free(temp), file);
}
