/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:50:23 by bammar            #+#    #+#             */
/*   Updated: 2022/12/27 22:04:45 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_pipe(char *line, int i, bool inside_quotes)
{
	if (line[i] == '|' && !inside_quotes && line[i + 1] != '|')
		if (i == 0 || (i != 0 && line[i - 1] != '|'))
			return (true);
	return (false);
}

size_t	ms_pipes_count(char *line)
{
	bool	inside_quotes;
	bool	inside_dquotes;
	int		i;
	size_t	count;

	inside_quotes = false;
	inside_dquotes = false;
	i = -1;
	count = 0;
	while (line[++i])
	{
		if (line[i] == '\"')
			inside_dquotes = !inside_dquotes;
		else if (line[i] == '\'')
			inside_quotes = !inside_quotes;
		else if (is_pipe(line, i, inside_quotes || inside_dquotes))
			count++;
	}
	return (count);
}
