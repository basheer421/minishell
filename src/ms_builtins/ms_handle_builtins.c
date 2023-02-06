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
	while (cmd && cmd[arg_count])
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

bool	exec_builtin_solo(t_cmd_chunk *chunk, t_ms *shell)
{
	int	og_stdin;
	int	og_stdout;
	int	cmd_is_builtin;

	og_stdin = dup(STDIN_FILENO);
	og_stdout = dup(STDOUT_FILENO);
	if (chunk->in_redir_fd > 0)
	{
		dup2(chunk->in_redir_fd, STDIN_FILENO);
		close(chunk->in_redir_fd);
	}
	if (chunk->out_redir_fd > 1)
	{
		dup2(chunk->out_redir_fd, STDOUT_FILENO);
		close(chunk->out_redir_fd);
	}
	cmd_is_builtin = handle_builtins(chunk->cmd, shell);
	dup2(og_stdin, STDIN_FILENO);
	dup2(og_stdout, STDOUT_FILENO);
	return (cmd_is_builtin);
}
