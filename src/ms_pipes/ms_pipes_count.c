/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:50:23 by bammar            #+#    #+#             */
/*   Updated: 2022/12/26 22:04:20 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (line[i] == '|' && !inside_quotes && !inside_dquotes
			&& line[i + 1] != '|')
			if (i == 0 || (i != 0 && line[i - 1] != '|'))
				count++;
	}
	return (count);
}
