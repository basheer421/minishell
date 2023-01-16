/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:03:05 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/10 19:03:05 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**dup_env_vars(t_ms *shell)
{
	char	**arr;
	t_node	*env;
	size_t		i;
	int		len;

	arr = (char **)ft_malloc(sizeof(char *) * (shell->env_vars->size + 1));
	env = *(shell->env_vars->array);
	i = -1;
	while (env)
	{
		len = ft_strlen(env->key) + 1;
		arr[++i] = (char *)ft_malloc(sizeof(char) * len);
		ft_strlcpy(arr[i], env->key, len);
		env = env->next;
	}
	arr[++i] = NULL;
	return (arr);
}

// creates a new array of a strings containing the env variables key values sorted in lexical order
static	char	**sort_lexical(t_ms *shell)
{
	size_t		i;
	size_t		j;
	char		*temp;
	char 		**env_keys;

	env_keys = dup_env_vars(shell);
	i = -1;
	while (env_keys[++i + 1])
	{
		j = i + 1;
		while (env_keys[++j])
			if (ft_strncmp(env_keys[i], env_keys[j], ft_strlen(env_keys[i])) > 0)
			{
				temp = env_keys[i];
				env_keys[i] = env_keys[j];
				env_keys[j] = temp;
			}
	}
	return (env_keys);
}

static void	display_sorted_env(t_ms *shell)
{
	char	**sorted_keys;
	char	*env_value;
	int		i;
	int		found;

	sorted_keys = sort_lexical(shell);
	i = -1;
	while (sorted_keys[++i])
	{
		found = 0;
		env_value = (char *)ht_get(shell->env_vars, sorted_keys[i], &found);
		if (env_value)
			printf("declare -x %s=\"%s\"\n", sorted_keys[i], env_value);
		else
			printf("declare -x %s\n", sorted_keys[i]);
		free(sorted_keys[i]);
	}
	free(sorted_keys);
}

void	export_var(t_ms *shell, char *env_var)
{
	char	*value_address;

	value_address = ft_strchr(env_var, '=');
	if (value_address)
	{
		*value_address = 0;
		if (ht_contains(shell->env_vars, env_var))
			ht_replace(shell->env_vars, env_var, value_address + 1);
		else
			ht_set(shell->env_vars, env_var, value_address + 1);
	}
	else
		ht_set(shell->env_vars, env_var, NULL);
}

void	ms_export(t_ms *shell, char **args, int arg_count)
{
	int		i;

	i = 0;
	if (arg_count == 1)
		display_sorted_env(shell);
	else
		while (args[++i])
		{
			if (args[i][0] == '=')
				printf("export: \'%s\': not a valid identifier\n", args[i]);
			else
				export_var(shell, args[i]);
		}
}
