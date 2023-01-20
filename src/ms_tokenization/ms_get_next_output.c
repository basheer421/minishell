/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_next_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:44:33 by bammar            #+#    #+#             */
/*   Updated: 2023/01/20 21:32:21 by bammar           ###   ########.fr       */
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

char	*ms_get_next_output(char **line_chunk)
{
	char		*name;
	int			len;
	t_inside	inside;

	ft_bzero(&inside, sizeof(inside));
	*line_chunk = ft_skip_spaces(ft_skip_spaces(*line_chunk) + 1);
	len = end_pos(*line_chunk, &inside);
	*line_chunk += inside.dquotes || inside.quotes;
	name = ft_malloc(len + 1);
	ft_strlcpy(name, *line_chunk, len + 1);
	*line_chunk += len + (inside.dquotes || inside.quotes);
	return (name);
}
