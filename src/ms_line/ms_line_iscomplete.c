/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_iscomplete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:47:00 by bammar            #+#    #+#             */
/*   Updated: 2023/01/27 20:26:24 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_inside
{
	bool	quotes;
	bool	dquotes;
}			t_inside;

static void	tick_inside_vars(t_inside *inside, char c)
{
	if (c == '\'' && !inside->dquotes)
		inside->quotes = !inside->quotes;
	else if (c == '\"' && !inside->quotes)
		inside->dquotes = !inside->dquotes;
}

static bool	contains_mutliquotes(char *line)
{
	t_inside	inside;
	int			i;

	ft_bzero(&inside, sizeof(t_inside));
	i = -1;
	while (line[++i])
	{
		tick_inside_vars(&inside, line[i]);
		if (line[i] && line[i + 1] == '|' && !inside.quotes && !inside.dquotes)
			return (true);
	}
	return (false);
}

static bool	contains_empty_str(char **str_chunks)
{
	int	i;

	i = -1;
	while (str_chunks[++i])
	{
		if (ft_strlen(str_chunks[i]) == 0)
			return (true);
	}
	return (false);
}

bool	ms_line_iscomplete(char *line, char **string_chunks)
{
	char	*nline;

	nline = ft_strtrim(line, " ");
	if (!nline)
		return (false);
	if (nline[0] == '|' || contains_mutliquotes(nline) || contains_empty_str(string_chunks))
		return (perror("syntax error near unexpected token `|'"),
			free(nline), false);
	if (nline[ft_strlen(nline) - 1] == '|')
		return (perror("syntax error near unexpected token `newline'"),
			free(nline), false);
	return (free(nline), true);
}
