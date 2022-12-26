/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:56:01 by bammar            #+#    #+#             */
/*   Updated: 2022/12/26 20:10:59 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	set_inside_ht(char **envp, t_ht *table)
{
	int		i;
	char	**splited_env_value;

	i = -1;
	while (envp[++i])
	{
		splited_env_value = ft_split(envp[i], '=');
		if (!splited_env_value)
			return (NULL);
		ht_set(table, splited_env_value[0], splited_env_value[1]);
	}
	return (free(splited_env_value), true);
}

t_ms	*ms_init(char **envp)
{
	t_ms	*shell;

	if (!envp || !*envp)
		return (NULL);
	shell = malloc(sizeof(t_ms));
	if (!shell)
		return (NULL);
	shell->current_dir = NULL; // Change this to be something
	shell->is_interactive_mode = true;
	shell->env_vars = ht_new(53);
	if (!shell->env_vars)
		return (NULL);
	if (!set_inside_ht(envp, shell->env_vars))
		return (free(shell), NULL);
	return (shell);
}
