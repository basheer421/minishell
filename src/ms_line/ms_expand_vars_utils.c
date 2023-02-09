/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_vars_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:19:11 by bammar            #+#    #+#             */
/*   Updated: 2023/02/09 13:38:47 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_index(char *line, char pos)
{
	if (line[pos + 1] == '?')
		return (pos + 2);
	return (ft_next_nonalnum(line, pos + 1));
}

char	*add_quotes(const char *str)
{
	char	*s;
	char	*temp;

	s = ft_strjoin("\"", str);
	if (!s)
		exit(EXIT_FAILURE);
	temp = s;
	s = ft_strjoin(s, "\"");
	if (!s)
		exit(EXIT_FAILURE);
	return (free(temp), s);
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
		return (add_quotes(val));
	}
	return (free(var), ft_strdup("\0"));
}
