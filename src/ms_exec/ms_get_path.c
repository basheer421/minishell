/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:10:06 by mfirdous          #+#    #+#             */
/*   Updated: 2023/02/19 16:45:16 by mfirdous         ###   ########.fr       */
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
		if (env->key && env->value)
		{
			len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
			envp[++i] = (char *)ft_malloc(sizeof(char) * len);
			ft_strlcpy(envp[i], env->key, len);
			ft_strlcat(envp[i], "=", len);
			ft_strlcat(envp[i], env->value, len);
		}
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
		mem->shell = shell;
	}
	return (mem);
}

// should i make it handle negative numbers and INTMAX/INTMIN?
static void	inc_shlvl(char *cmd_name, char **envp)
{
	int		len;
	int		i;
	char	*new_shlvl;

	len = ft_strlen(cmd_name);
	if (ft_strncmp(cmd_name, "minishell", len) == 0 || \
		ft_strncmp(cmd_name, "./minishell", len) == 0)
	{
		i = -1;
		while (envp[++i])
		{
			if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
			{
				new_shlvl = ft_itoa(ft_atoi(ft_strchr(envp[i], '=') + 1) + 1);
				free(envp[i]);
				envp[i] = ft_strjoin("SHLVL=", new_shlvl);
				free(new_shlvl);
				break ;
			}
		}
	}
}

t_alloced	*ms_get_path(int p1[], int p2[], t_ms *shell, int i)
{
	char		*path_name;
	t_alloced	*cmd_info;
	char		**cmd;

	cmd_info = set_alloc(p1, p2, shell);
	cmd = shell->cur_cmd[i]->cmd;
	if (!cmd || !cmd[0])
		exit_msg(NULL, NULL, 0, cmd_info);
	path_name = NULL;
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], X_OK) == -1)
			exit_msg(cmd[0], strerror(errno), get_exit_status(errno), cmd_info);
		if (!is_regular_file(cmd[0]))
			exit_msg(cmd[0], IS_A_DIR_ERR, 126, cmd_info);
		path_name = ft_strdup(cmd[0]);
	}
	else
		path_name = get_pathname(cmd[0], cmd_info->envp);
	if (!path_name)
		exit_msg(cmd[0], CMD_ERR, 127, cmd_info);
	cmd_info->path = path_name;
	if (access(path_name, X_OK) != 0)
		exit_msg(cmd[0], PERMISSION_ERR, 126, cmd_info);
	inc_shlvl(cmd[0], cmd_info->envp);
	return (cmd_info);
}
