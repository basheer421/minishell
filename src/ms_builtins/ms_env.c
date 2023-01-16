/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:41:37 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/10 17:41:37 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(t_ms *shell)
{
	t_node	*var;
	char	*var_value;
	int		found;

	var = *(shell->env_vars->array);
	while (var)
	{
		found = 0;
		var_value = (char *)ht_get(shell->env_vars, var->key, &found);
		if (var_value)
			printf("%s=%s\n", var->key, var_value);
		var = var->next;
	}
}