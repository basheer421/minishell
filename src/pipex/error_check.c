/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:10:06 by mfirdous          #+#    #+#             */
/*   Updated: 2023/02/08 17:10:32 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_envp(t_ms *shell)
{
	char	**envp;
	t_node	*env;
	size_t	i;
	int		len;

	envp = (char **)ft_malloc(sizeof(char *) * (shell->env_vars->size + 1));
	env = *(shell->env_vars->array);
	i = -1;
	while (env)
	{
		len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
		envp[++i] = (char *)ft_malloc(sizeof(char) * len);
		ft_strlcpy(envp[i], env->key, len);
		ft_strlcat(envp[i], "=", len);
		ft_strlcat(envp[i], env->value, len);
		env = env->next;
	}
	envp[++i] = NULL;
	return (envp);
}

t_alloced	*set_alloc(int p1[], int p2[], t_ms *shell)
{	
	t_alloced	*mem;

	mem = (t_alloced *)malloc(sizeof(t_alloced));
	if (mem)
	{
		mem->pipes[0][0] = p1[0];
		mem->pipes[0][1] = p1[1];
		mem->pipes[1][0] = p2[0];
		mem->pipes[1][1] = p2[1];
		mem->path = NULL;
		mem->envp = create_envp(shell);
	}
	return (mem);
}

void	exit_msg(char *heading, char *err_msg, int err_code, t_alloced *mem)
{
	int	i;

	i = -1;
	write(STDERR_FILENO, heading, ft_strlen(heading));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
	// ft_printf("%s: %s\n", heading, err_msg);
	if (mem)
	{
		while (++i < 2)
		{
			if (mem->pipes[i][i])
				close(mem->pipes[i][i]);
			if (mem->pipes[i][!i])
				close(mem->pipes[i][!i]);
		}
		free(mem->path);
		// free_strs(mem->cmd, mem->path, 0);
		ft_split_destroy(mem->envp);
		free(mem);
	}
	exit(err_code);
}

// check in PATH only if it doesnt contain a /, check dir
t_alloced	*check_cmd_path(int p1[], int p2[], char **cmd, t_ms *shell)
{
	char		*path_name;
	t_alloced	*cmd_info;

	cmd_info = set_alloc(p1, p2, shell);
	if (!cmd || !cmd[0])
		exit_msg("", CMD_ERR, 127, cmd_info);
	path_name = get_pathname(cmd[0], cmd_info->envp);
	// only check if its an abs path if it has /s
	if (!path_name && access(cmd[0], F_OK) == 0)
		path_name = ft_strdup(cmd[0]);
	else if (!path_name)
		exit_msg(cmd[0], CMD_ERR, 127, cmd_info);
	cmd_info->path = path_name;
	if (access(path_name, X_OK) != 0)
		exit_msg(cmd[0], PERMISSION_ERR, 126, cmd_info);
	check_cmd_minishell(cmd[0], cmd_info->envp);
	return (cmd_info);
}

int	check_err(char *func_name, int ret_value)
{
	if (ret_value == -1)
	{
		perror(func_name);
		exit(EXIT_FAILURE);
	}
	return (ret_value);
}
