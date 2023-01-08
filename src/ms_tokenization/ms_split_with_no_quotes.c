/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_with_no_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:18:11 by bammar            #+#    #+#             */
/*   Updated: 2023/01/08 21:20:29 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			len++;
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
		if (line[i] == '\"')
			inside_dquotes = !inside_dquotes;
		else if (line[i] == '\'')
			inside_quotes = !inside_quotes;
		else if (line[i] == c && !inside_dquotes && !inside_quotes)
			positions[current_index++] = i;
	}
	positions[current_index] = -1;
	return (positions);
}

static size_t	get_length(char *line, int current_index, int position)
{
	if (position == -1)
		return (ft_strlen(line) - current_index);
	return (position - current_index);
}

char	**split_with_no_quotes(char *line, int c)
{
	char	**content;
	int		current_index;
	int		*positions;
	size_t	i;
	size_t	content_size;

	content_size = split_with_no_quotes_len(line, c) + 1;
	positions = ms_char_positions(line, c);
	if (!positions)
		return (NULL);
	content = malloc(sizeof(char *) * (content_size + 1));
	if (!content)
		return (NULL);
	i = 0;
	current_index = 0;
	while (i < content_size)
	{
		content[i] = ft_substr(line, current_index, get_length(line,
					current_index, positions[i]));
		if (!content[i])
			return (free(positions), free(content), NULL);
		current_index = positions[i++] + 1;
	}
	content[i] = NULL;
	return (free(positions), content);
}
