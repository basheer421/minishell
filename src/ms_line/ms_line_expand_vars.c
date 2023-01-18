/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_expand_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:30:45 by bammar            #+#    #+#             */
/*   Updated: 2023/01/18 21:25:59 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_inside
{
	bool	quotes;
	bool	dquotes;
	bool	var;
	char	*value;
}			t_inside;

static void	tick_inside_vars(t_inside *inside, char c, char next)
{
	if (c == '\'' && !inside->dquotes)
		inside->quotes = !inside->quotes;
	else if (c == '\"' && !inside->quotes)
		inside->dquotes = !inside->dquotes;
	else if (c == '$' && !inside->quotes && (ft_isalnum(next) || next == '?'))
		inside->var = true;
	else if (!ft_isalnum(c) || c != '?')
		inside->var = false;
}

static int	len_with_expand(char *line, t_ms *shell)
{
	int			i;
	int			total;
	char		*value;
	t_inside	inside;

	ft_bzero(&inside, sizeof(t_inside));
	total = 0;
	i = -1;
	while (line[++i])
	{
		tick_inside_vars(&inside, line[i], line[i + 1]);
		if (inside.var)
		{
			value = value_at(line, i, shell);
			if (!value)
				exit(EXIT_FAILURE);
			total += ft_strlen(value);
			free(value);
			i = get_next_index(line, i) - 1;
		}
		else
			total++;
	}
	return (total);
}

static char	*var_init(t_inside *inside, char **line, t_ms *shell, int *c_count)
{
	char	*nline;

	inside->dquotes = 0;
	inside->quotes = 0;
	inside->value = NULL;
	inside->var = 0;
	nline = ft_malloc(sizeof(int) * (len_with_expand(*line, shell) + 1));
	*c_count = 0;
	return (nline);
}

void	ms_line_expand_vars(char **line, t_ms *shell)
{
	int			c_count;
	char		*nline;
	t_inside	inside;
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
			i = get_next_index(*line, i) - 1;
		}
		else
			nline[c_count++] = line[0][i];
	}
	nline[c_count] = 0;
	free(*line);
	*line = nline;
}
