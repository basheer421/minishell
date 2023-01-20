/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_vars_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:19:11 by bammar            #+#    #+#             */
/*   Updated: 2023/01/20 18:40:55 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_index(char *line, char pos)
{
	if (line[pos + 1] == '?')
		return (pos + 2);
	return (ft_next_nonalnum(line, pos + 1));
}

char	*value_at(char *line, int pos, t_ms *shell)
{
	char	*var;
	char	*val;

	if (line[pos + 1] == '?')
		return (ft_itoa(g_exit_code));
		// return (ft_itoa(shell->error_code));
		// put here the prev error code {$?}
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
