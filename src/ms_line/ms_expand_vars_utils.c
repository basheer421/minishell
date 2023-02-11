/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_vars_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:19:11 by bammar            #+#    #+#             */
/*   Updated: 2023/02/11 22:41:25 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_index(char *line, char pos)
{
	if (line[pos + 1] == '?')
		return (pos + 2);
	return (ft_next_nonalnum(line, pos + 1));
}

// add only around tokens
static char	*add_tokenquotes(char *str)
{
	char	*temp;

	if (*ft_skip_spaces(str) == '\"' || *ft_skip_spaces(str) == '\'')
		return (ft_strdup(str));
	temp = ft_strfjoin(ft_strdup("\""), ft_strdup(str));
	temp = ft_strfjoin(ft_strdup(temp), ft_strdup("\""));
	return (temp);
}

static char	*join_split(char **arr)
{
	int		i;
	char	*big;

	i = -1;
	big = ft_strdup("\0");
	while (arr[++i])
	{
		if (arr[i + 1])
			big = ft_strfjoin(big, ft_strfjoin(arr[i], ft_strdup(" ")));
		else
			big = ft_strfjoin(big, arr[i]);
	}
	return (big);
}

static char	*fix_quotes(char *str, char c)
{
	char	**arr;
	char	*temp;
	int		i;

	arr = split_with_no_quotes(str, c);
	if (!arr)
		exit(EXIT_FAILURE);
	i = -1;
	while (arr[++i])
	{
		temp = arr[i];
		arr[i] = add_tokenquotes(arr[i]);
		free(temp);
	}
	return (join_split(arr));
}

char	*value_at(char *line, int pos, t_ms *shell)
{
	char	*var;
	char	*val;

	if (line[pos + 1] == '?')
		return (ft_itoa(g_exit_status));
	var = ft_substr(line, pos + 1, ft_next_nonalnum(line, pos + 1) - pos - 1);
	if (ht_contains(shell->env_vars, var))
	{
		val = ht_get(shell->env_vars, var);
		free(var);
		if (!val)
			return (ft_strdup("\0"));
		return (fix_quotes(val, ' '));
	}
	return (free(var), ft_strdup("\0"));
}
