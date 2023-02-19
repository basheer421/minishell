/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_next_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:17:25 by bammar            #+#    #+#             */
/*   Updated: 2023/02/12 21:25:32 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_file	*ms_get_next_redirect(char *line_chunk, char type, int *ptr)
{
	int			len;
	t_inside	inside;
	t_file		*file;
	char		*temp;

	ft_bzero(&inside, sizeof(inside));
	file = ft_malloc(sizeof(t_file));
	*ptr += ft_skip_spaces(line_chunk + *ptr) - (line_chunk + *ptr);
	*ptr += 1;
	file->is_extra = line_chunk[*ptr] == type;
	*ptr += file->is_extra;
	*ptr += ft_skip_spaces(line_chunk + *ptr) - (line_chunk + *ptr);
	len = end_pos((line_chunk + *ptr), &inside);
	if (len == 0)
	{
		g_exit_status = UNEXPECTED_TOKEN;
		return (ft_putendl_fd("syntax error, unexpected token", 2), free(file),
			NULL);
	}
	*ptr += (inside.dquotes || inside.quotes);
	file->name = ft_substr((line_chunk + *ptr), 0, len);
	temp = file->name;
	file->name = ft_exclude_quotes(file->name);
	*ptr += len + (inside.dquotes || inside.quotes);
	return (free(temp), file);
}
