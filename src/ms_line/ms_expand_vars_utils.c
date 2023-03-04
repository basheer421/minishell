/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_vars_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:19:11 by bammar            #+#    #+#             */
/*   Updated: 2023/03/04 17:56:11 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_index(char *line, int pos)
{
	if (line[pos + 1] == '?')
		return (pos + 2);
	return (ft_next_nonalnum(line, pos + 1));
}

// add only around tokens
static char	*add_tokenquotes(char *str)
{
	char	*temp;

	if (ft_strncmp(ft_skip_spaces(str), "\'", 1) == 0
		|| ft_strncmp(ft_skip_spaces(str), "\"", 1) == 0)
		return (ft_strdup(str));
	temp = ft_strfjoin(ft_strdup("\""), ft_strdup(str));
	temp = ft_strfjoin(temp, ft_strdup("\""));
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
			big = ft_strfjoin(big, ft_strfjoin(ft_strdup(arr[i]),
						ft_strdup(" ")));
		else
			big = ft_strfjoin(big, ft_strdup(arr[i]));
	}
	return (big);
}

static char	*fix_quotes(char *str, char c)
{
	char	**arr;
	char	*temp;
	char	*nstr;
	int		i;

	if (!str)
		return (ft_strdup("\'\'"));
	arr = split_with_no_quotes(str, c);
	if (!arr)
		return (ft_strdup("\'\'"));
	i = -1;
	while (arr[++i])
	{
		temp = arr[i];
		arr[i] = add_tokenquotes(arr[i]);
		free(temp);
	}
	nstr = join_split(arr);
	return (ft_split_destroy(arr), nstr);
}

char	*value_at(char *line, int pos, t_ms *shell, bool wrap)
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
		if (wrap)
			return (fix_quotes(val, ' '));
		return (ft_strdup(val));
	}
	if (wrap)
		return (free(var), fix_quotes(NULL, ' '));
	return (free(var), ft_strdup("\0"));
}
