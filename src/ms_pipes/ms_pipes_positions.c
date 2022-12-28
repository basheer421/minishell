/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes_positions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:11:24 by bammar            #+#    #+#             */
/*   Updated: 2022/12/28 15:17:28 by bammar           ###   ########.fr       */
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

int	*ms_pipes_positions(char *line)
{
	int		*positions;
	int		i;
	int		current_index;
	bool	inside_quotes;
	bool	inside_dquotes;

	positions = malloc(sizeof(int) * (ms_pipes_count(line) + 1));
	if (!positions)
		return (NULL);
	inside_quotes = false;
	inside_dquotes = false;
	i = -1;
	current_index = 0;
	while (line[++i])
	{
		if (line[i] == '\"')
			inside_dquotes = !inside_dquotes;
		else if (line[i] == '\'')
			inside_quotes = !inside_quotes;
		else if (is_pipe(line, i, inside_quotes || inside_dquotes))
			positions[current_index++] = i;
	}
	positions[current_index] = -1;
	return (positions);
}
