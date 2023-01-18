/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_expand_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:30:45 by bammar            #+#    #+#             */
/*   Updated: 2023/01/18 17:10:13 by mfirdous         ###   ########.fr       */
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

static void	tick_inside_vars(t_inside *inside, char c, bool is_end)
{
	if (c == '\'' && !inside->dquotes)
		inside->quotes = !inside->quotes;
	else if (c == '\"' && !inside->quotes)
		inside->dquotes = !inside->dquotes;
	else if (c == '$' && !inside->quotes && !is_end)
		inside->var = true;
	else if (!ft_isalnum(c) && c != '?')
		inside->var = false;
}

static char	*value_at(char *line, int pos, t_ms *shell)
{
	char	*var;
	char	*val;

	var = ft_substr(line, pos + 1, ft_next_nonalnum(line, pos + 1) - pos - 1);
	if (ht_contains(shell->env_vars, var))
	{
		val = ht_get(shell->env_vars, var);
		free(var);
		if (!val)
			return (ft_strdup("\0"));
		return (ft_strdup(val));
	}
	return (free(var), ft_strdup("\0"));
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
		tick_inside_vars(&inside, line[i], line[i + 1] == 0);
		if (inside.var)
		{
			value = value_at(line, i, shell);
			if (!value)
				exit(EXIT_FAILURE);
			total += ft_strlen(value);
			free(value);
			i = ft_next_nonalnum(line, i + 1) - 1;
		}
		else
			total++;
	}
	return (total);
}

static char	*var_init(t_inside *inside, char **line, t_ms *shell)
{
	char	*nline;

	ft_bzero(&inside, sizeof(t_inside));
	nline = ft_malloc(sizeof(int) * (len_with_expand(*line, shell) + 1));
	return (nline);
}

void	ms_line_expand_vars(char **line, t_ms *shell)
{
	int			c_count;
	char		*nline;
	t_inside	inside;
	int			i;

	nline = var_init(&inside, line, shell);
	c_count = 0;
	i = -1;
	while (line[0][++i])
	{
		tick_inside_vars(&inside, line[0][i], line[0][i + 1] == 0);
		if (inside.var)
		{
			inside.value = value_at(*line, i, shell);
			ft_memcpy(nline + c_count, inside.value, ft_strlen(inside.value));
			c_count += ft_strlen(inside.value);
			free(inside.value);
			i = ft_next_nonalnum(*line, i + 1) - 1;
		}
		else
			nline[c_count++] = line[0][i];
	}
	nline[c_count] = 0;
	free(*line);
	*line = nline;
}
