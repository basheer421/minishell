/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_expand_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:30:45 by bammar            #+#    #+#             */
/*   Updated: 2023/02/26 14:53:01 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tick_inside_vars(t_inside2 *inside, char c, char next)
{
	if (c == '\'' && !inside->dquotes)
		inside->quotes = !inside->quotes;
	else if (c == '\"' && !inside->quotes)
		inside->dquotes = !inside->dquotes;
	else if (c == '<' && next == '<'
		&& !inside->quotes && !inside->dquotes)
		inside->heredoc = true;
	else if (inside->heredoc && c == '<'
		&& !inside->quotes && !inside->dquotes)
		inside->skipping = true;
	else if (inside->heredoc && c == ' '
		&& !inside->skipping
		&& !inside->quotes && !inside->dquotes)
		inside->heredoc = false;
	else if (c == '$' && !inside->quotes
		&& !inside->heredoc && (ft_isalpha(next) || next == '?'))
		inside->var = true;
}

static int	len_with_expand(char *line, t_ms *shell)
{
	int			i;
	int			total;
	char		*value;
	t_inside2	inside;

	ft_bzero(&inside, sizeof(t_inside2));
	total = 0;
	i = -1;
	while (line[++i])
	{
		tick_inside_vars(&inside, line[i], line[i + 1]);
		if (inside.var)
		{
			value = value_at(line, i, shell);
			total += ft_strlen(value);
			free(value);
			inside.var = false;
			i = get_next_index(line, i) - 1;
		}
		else
			total++;
	}
	return (total);
}

static char	*var_init(t_inside2 *inside, char **line, t_ms *shell, int *c_count)
{
	char	*nline;

	ft_bzero(inside, sizeof(t_inside2));
	inside->value = NULL;
	nline = ft_malloc(len_with_expand(*line, shell) + 1);
	*c_count = 0;
	return (nline);
}

void	ms_line_expand_vars(char **line, t_ms *shell)
{
	int			c_count;
	char		*nline;
	t_inside2	inside;
	int			i;

	nline = var_init(&inside, line, shell, &c_count);
	i = -1;
	while (line[0][++i])
	{
		tick_inside_vars(&inside, line[0][i], line[0][i + 1]);
		if (inside.var)
		{
			inside.value = value_at(*line, i, shell);
			ft_memcpy(nline + c_count, inside.value, ft_strlen(inside.value));
			c_count += ft_strlen(inside.value);
			free(inside.value);
			inside.var = false;
			i = get_next_index(*line, i) - 1;
		}
		else
			nline[c_count++] = line[0][i];
	}
	nline[c_count] = 0;
	free(*line);
	*line = nline;
}
