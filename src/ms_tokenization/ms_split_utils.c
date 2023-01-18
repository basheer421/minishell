/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:01:38 by bammar            #+#    #+#             */
/*   Updated: 2023/01/18 17:02:47 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_split_postions
{
	int		current_index;
	int		*positions;
	bool	inside_quotes;
	bool	inside_dquotes;
}			t_split_postions;

char	*chrskip(char *s, char c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != 0 && s[i] == c)
		i++;
	return (s + i);
}

int	split_with_no_quotes_len(char *line, int c)
{
	int		i;
	int		len;
	bool	inside_quotes;
	bool	inside_dquotes;

	inside_quotes = false;
	inside_dquotes = false;
	i = -1;
	len = 0;
	while (line[++i])
	{
		if (line[i] == c && !inside_quotes && !inside_dquotes)
		{
			len++;
			while (line[i + 1] == c)
				i++;
		}
		else if (line[i] == '\'')
			inside_quotes = !inside_quotes;
		else if (line[i] == '\"')
			inside_dquotes = !inside_dquotes;
	}
	return (len);
}

int	*ms_char_positions(char *line, int c)
{
	t_split_postions	vars;
	int					i;

	ft_bzero(&vars, sizeof(t_split_postions));
	vars.positions = malloc(sizeof(int) * (split_with_no_quotes_len(line, c)
				+ 1));
	if (!vars.positions)
		return (NULL);
	i = -1;
	while (line[++i])
	{
		if (line[i] == c && !vars.inside_dquotes && !vars.inside_quotes)
		{
			vars.positions[vars.current_index++] = i;
			while (line[i + 1] == c)
				i++;
		}
		else if (line[i] == '\"')
			vars.inside_dquotes = !vars.inside_dquotes;
		else if (line[i] == '\'')
			vars.inside_quotes = !vars.inside_quotes;
	}
	vars.positions[vars.current_index] = -1;
	return (vars.positions);
}
