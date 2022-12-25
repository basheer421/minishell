/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:10:06 by mfirdous          #+#    #+#             */
/*   Updated: 2022/09/21 16:25:04 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_alloced	*set_alloc(int p1[], int p2[], char **cmd, char *path)
{	
	t_alloced	*mem;

	mem = (t_alloced *)malloc(sizeof(t_alloced));
	if (mem)
	{
		mem->pipes[0][0] = p1[0];
		mem->pipes[0][1] = p1[1];
		mem->pipes[1][0] = p2[0];
		mem->pipes[1][1] = p2[1];
		mem->cmd = cmd;
		mem->path = path;
	}
	return (mem);
}

void	exit_msg(char *heading, char *err_msg, int err_code, t_alloced *mem)
{
	int	i;

	i = -1;
	ft_printf("%s: %s\n", heading, err_msg);
	if (mem)
	{
		while (++i < 2)
		{
			if (mem->pipes[i][i])
				close(mem->pipes[i][i]);
			if (mem->pipes[i][!i])
				close(mem->pipes[i][!i]);
		}
		free_strs(mem->cmd, mem->path, 0);
		free(mem);
	}
	exit(err_code);
}

t_alloced	*check_cmd(int p1[], int p2[], char *cmd_str, char **envp)
{
	char		**cmd;
	char		*path_name;
	t_alloced	*cmd_info;

	cmd_info = set_alloc(p1, p2, 0, 0);
	if (!cmd_str || !cmd_str[0])
		exit_msg("pipex", EMPTY_STRING_ERR, 2, cmd_info);
	cmd = ft_split(cmd_str, ' ');
	cmd_info->cmd = cmd;
	if (!cmd || !cmd[0])
		exit_msg(cmd_str, CMD_ERR, 127, cmd_info);
	path_name = get_pathname(cmd[0], envp);
	if (!path_name && access(cmd[0], F_OK) == 0)
		path_name = ft_strdup(cmd[0]);
	else if (!path_name)
		exit_msg(cmd[0], CMD_ERR, 127, cmd_info);
	cmd_info->path = path_name;
	if (access(path_name, X_OK) != 0)
		exit_msg(cmd[0], PERMISSION_ERR, 126, cmd_info);
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
