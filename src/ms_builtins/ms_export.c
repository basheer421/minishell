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

// Copies the env variables key values into a new array of strings
static	char	**dup_env_vars(t_ms *shell)
{
	char	**arr;
	t_node	*env;
	size_t	i;
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

// Creates a new array of a strings containing the env vars key values sorted
static	char	**sort_lexical(t_ms *shell)
{
	size_t		i;
	size_t		j;
	char		*temp;
	char		**keys;

	keys = dup_env_vars(shell);
	i = -1;
	while (keys[++i + 1])
	{
		j = i + 1;
		while (keys[++j])
		{
			if (ft_strncmp(keys[i], keys[j], ft_strlen(keys[i])) > 0)
			{
				temp = keys[i];
				keys[i] = keys[j];
				keys[j] = temp;
			}
		}
	}
	return (keys);
}

static void	display_sorted_env(t_ms *shell)
{
	char	**sorted_keys;
	char	*env_value;
	int		i;

	sorted_keys = sort_lexical(shell);
	i = -1;
	while (sorted_keys[++i])
	{
		env_value = (char *)ht_get(shell->env_vars, sorted_keys[i]);
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

int	ms_export(t_ms *shell, char **args, int arg_count)
{
	int	i;

	i = 0;
	if (arg_count == 1)
		display_sorted_env(shell);
	else
	{
		while (args[++i])
		{
			if (args[i][0] == '=')
			{
				printf("export: \'%s\': not a valid identifier\n", args[i]);
				// return (EXIT_FAILURE);
			}
			else
				export_var(shell, args[i]);
		}
	}
	return (EXIT_SUCCESS);
}
