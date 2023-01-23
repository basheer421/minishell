/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:39:03 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/10 16:39:03 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **cmd)
{
	int	arg_count;

	arg_count = 0;
	while (cmd[arg_count])
		arg_count++;
	return (arg_count);
}

bool	handle_builtins(char **cmd, t_ms *shell)
{
	int		arg_count;
	bool	builtin_flag;

	builtin_flag = true;
	arg_count = count_args(cmd);
	if (cmd && cmd[0])
	{
		if (ft_strncmp(cmd[0], "echo", 5) == 0)
				g_exit_status = ms_echo(cmd, (cmd[1] && \
								ft_strncmp(cmd[1], "-n", 2) == 0));
		else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
			g_exit_status = ms_pwd();
		else if (ft_strncmp(cmd[0], "exit", 5) == 0)
			g_exit_status = ms_exit(cmd, arg_count, shell);
		else if (ft_strncmp(cmd[0], "cd", 3) == 0)
			g_exit_status = ms_cd(shell, cmd, arg_count);
		else if (ft_strncmp(cmd[0], "env", 4) == 0)
			g_exit_status = ms_env(shell);
		else if (ft_strncmp(cmd[0], "export", 7) == 0)
			g_exit_status = ms_export(shell, cmd, arg_count);
		else if (ft_strncmp(cmd[0], "unset", 6) == 0)
			g_exit_status = ms_unset(shell, cmd, arg_count);
		else
			builtin_flag = false;
	}
	return (builtin_flag);
}

// int	handle_builtins(char *cmd_str, t_ms *shell)
// {
// 	int		arg_count;
// 	char	**cmd;
// 	bool	builtin_flag;

// 	cmd = ft_split2(cmd_str, " ", &arg_count);
// 	builtin_flag = true;
// 	if (cmd && cmd[0])
// 	{
// 		if (ft_strncmp(cmd[0], "echo", 5) == 0)
// 				g_exit_status = ms_echo(cmd, (cmd[1] && \
// 								ft_strncmp(cmd[1], "-n", 2) == 0));
// 		else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
// 			g_exit_status = ms_pwd();
// 		else if (ft_strncmp(cmd[0], "exit", 5) == 0)
// 			g_exit_status = ms_exit(cmd, arg_count, shell);
// 		else if (ft_strncmp(cmd[0], "cd", 3) == 0)
// 			g_exit_status = ms_cd(shell, cmd, arg_count);
// 		else if (ft_strncmp(cmd[0], "env", 4) == 0)
// 			g_exit_status = ms_env(shell);
// 		else if (ft_strncmp(cmd[0], "export", 7) == 0)
// 			g_exit_status = ms_export(shell, cmd, arg_count);
// 		else if (ft_strncmp(cmd[0], "unset", 6) == 0)
// 			g_exit_status = ms_unset(shell, cmd, arg_count);
// 		else
// 			builtin_flag = false;
// 		ft_split_destroy(cmd);
// 	}
// 	return (builtin_flag);
// }
