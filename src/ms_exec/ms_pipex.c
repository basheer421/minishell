/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:57:10 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/23 18:57:10 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	redirect_stdinout(t_cmd_chunk **cmd, int i, int p1[], int p2[])
{
	if (cmd[i]->in_fd == 0)
	{
		if (i > 0)
			dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
	}
	else if (cmd[i]->in_fd > 0)
	{
		dup2(cmd[i]->in_fd, STDIN_FILENO);
		close(p1[0]);
	}
	if (cmd[i]->out_fd == 0)
	{
		if (cmd[i + 1])
			dup2(p2[1], STDOUT_FILENO);
		close(p2[1]);
	}
	else if (cmd[i]->out_fd > 0)
	{
		dup2(cmd[i]->out_fd, STDOUT_FILENO);
		close(p2[1]);
	}
}

static int	exec_cmd(int p1[], int p2[], t_ms *shell, int i)
{
	int			pid;
	t_alloced	*c;

	signal(SIGINT, ms_child_sigint_handler);
	signal(SIGQUIT, ms_sigquit_handler);
	pid = check_err("fork", fork());
	if (pid == 0)
	{
		close(p2[0]);
		redirect_stdinout(shell->cur_cmd, i, p1, p2);
		ms_fds_close(shell->cur_cmd);
		if (shell->cur_cmd[i]->in_fd == -1 || shell->cur_cmd[i]->out_fd == -1)
			exit_msg(NULL, NULL, g_exit_status, set_alloc(p1, p2, shell));
		if (handle_builtins(shell, i, get_builtin_no(shell->cur_cmd[i]->cmd)))
			exit_msg(NULL, NULL, g_exit_status, set_alloc(p1, p2, shell));
		c = ms_get_path(p1, p2, shell, i);
		if (execve(c->path, shell->cur_cmd[i]->cmd, c->envp) == -1)
			exit_msg("execve", strerror(errno), EXIT_FAILURE, c);
	}
	return (pid);
}

static int	wait_cmds(t_ms *shell, int count)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < count)
		if (shell->pids[i] != -1)
			waitpid(shell->pids[i], &status, 0);
	free(shell->pids);
	shell->pids = NULL;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (ms_get_sig_status(WTERMSIG(status)));
	return (1);
}

static int	exec_init(int p[], t_ms *shell, int cmd_count)
{
	if (check_err("pipe", pipe(p)) == -1)
		return (EXIT_FAILURE);
	close(p[1]);
	shell->pids = (int *)malloc(sizeof(int) * (cmd_count));
	if (!shell->pids)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ms_pipex(t_ms *shell, int cmd_count)
{	
	int			p[2][2];
	int			i;
	int			pipe_no;

	if (exec_init(p[0], shell, cmd_count) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pipe_no = 0;
	i = -1;
	while (shell->cur_cmd[++i])
	{
		if (check_err("pipe", pipe(p[!pipe_no])) == -1)
		{
			free(shell->pids);
			return (EXIT_FAILURE);
		}
		// if (shell->cur_cmd[i]->in_fd != -1 && shell->cur_cmd[i]->out_fd != -1)
		// {
			shell->pids[i] = exec_cmd(p[pipe_no], p[!pipe_no], shell, i);
		// }
		// else
		// {
			// printf("%d cmd wont run\n", i);
			// shell->pids[i] = -1;
		// }
		close(p[pipe_no][0]);
		close(p[!pipe_no][1]);
		pipe_no = !pipe_no;
	}
	close(p[pipe_no][0]);
	return (wait_cmds(shell, i));
}
