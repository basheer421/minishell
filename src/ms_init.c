/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:56:01 by bammar            #+#    #+#             */
/*   Updated: 2023/02/09 13:53:02 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_index(char c, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

// Incase there is something like this: ENV_VAR="something=something"
static char	**split_by_first(char c, char *str)
{
	char	*s1;
	char	*s2;
	char	**a;

	s1 = ft_substr(str, 0, get_index(c, str));
	if (!s1)
		return (NULL);
	s2 = ft_substr(str, get_index(c, str) + 1, ft_strlen(ft_strchr(str, c)
				+ 1));
	if (!s2)
		return (free(s1), NULL);
	a = malloc(3 * sizeof(char *));
	if (!a)
		return (free(s1), free(s2), NULL);
	a[0] = s1;
	a[1] = s2;
	a[2] = NULL;
	return (a);
}

static bool	fill_ht(char **envp, t_ht *table)
{
	int		i;
	char	**splited_env_value;

	if (!envp)
		return (true);
	i = -1;
	while (envp[++i])
	{
		splited_env_value = split_by_first('=', envp[i]);
		if (!splited_env_value)
			return (false);
		if (!splited_env_value[1] || ft_strlen(splited_env_value[1]) == 0)
		{
			free(splited_env_value[1]);
			splited_env_value[1] = ft_strdup("\0");
		}
		if (!splited_env_value[1])
			return (free(splited_env_value[0]),
				free(splited_env_value), false);
		ht_set(table, splited_env_value[0], splited_env_value[1]);
		ft_split_destroy(splited_env_value);
	}
	return (true);
}

t_ms	*ms_init(char **envp)
{
	t_ms	*shell;

	shell = ft_calloc(1, sizeof(t_ms));
	if (!shell)
		return (NULL);
	shell->current_dir = getcwd(shell->current_dir, 0);
	if (!shell->current_dir)
		return (NULL);
	shell->is_interactive_mode = true;
	shell->env_vars = ht_new(1);
	if (!shell->env_vars)
		return (NULL);
	if (!fill_ht(envp, shell->env_vars))
		return (free(shell), NULL);
	return (shell);
}

void	ms_destroy(t_ms *shell)
{
	if (shell->current_dir)
		free(shell->current_dir);
	if (shell->env_vars)
		ht_destroy(shell->env_vars);
	free(shell);
}
