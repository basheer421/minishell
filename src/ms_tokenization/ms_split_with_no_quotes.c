/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_with_no_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:18:11 by bammar            #+#    #+#             */
/*   Updated: 2023/01/12 12:39:20 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*chrskip(char *s, char c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != 0 && s[i] == c)
		i++;
	return (s + i);
}


static int	split_with_no_quotes_len(char *line, int c)
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

static int	*ms_char_positions(char *line, int c)
{
	int		*positions;
	int		i;
	int		current_index;
	bool	inside_quotes;
	bool	inside_dquotes;

	positions = malloc(sizeof(int) * (split_with_no_quotes_len(line, c) + 1));
	if (!positions)
		return (NULL);
	inside_quotes = false;
	inside_dquotes = false;
	i = -1;
	current_index = 0;
	while (line[++i])
	{
		if (line[i] == c && !inside_dquotes && !inside_quotes)
		{
			positions[current_index++] = i;
			while (line[i + 1] == c)
				i++;
		}
		else if (line[i] == '\"')
			inside_dquotes = !inside_dquotes;
		else if (line[i] == '\'')
			inside_quotes = !inside_quotes;
		
	}
	positions[current_index] = -1;
	return (positions);
}

static size_t	get_length(char *line, char *start_pos, int next_c)
{
	if (next_c == -1)
		return (ft_strlen(start_pos));
	return (ft_strlen(start_pos) - ft_strlen(line + next_c));
}

char	**split_with_no_quotes(char *line, int c)
{
	char	**content;
	int		current_index;
	int		*positions;
	char	*start_pos;
	size_t	i;
	size_t	content_size;

	while (*line == c)
		line++;
	if (!line || !*line)
		return (NULL);
	content_size = split_with_no_quotes_len(line, c) + 1;
	positions = ms_char_positions(line, c);
	if (!positions)
		return (NULL);
	content = malloc(sizeof(char *) * (content_size + 1));
	if (!content)
		return (free(positions), NULL);
	i = 0;
	current_index = 0;
	while (i < content_size)
	{
		start_pos = chrskip(line + current_index, c);
		if (!start_pos || !*start_pos)
			return (free(positions), free(content), NULL);
		content[i] = ft_substr(start_pos,
			0, get_length(line,
					start_pos, positions[i]));
		if (!content[i])
			return (free(positions), free(content), NULL);
		current_index = positions[i++] + 1;
	}
	content[i] = NULL;
	return (free(positions), content);
}

// hello  "wow lol"  rld
// 6 - 3 = 5