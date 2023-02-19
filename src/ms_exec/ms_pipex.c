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
		// close(p1[1]);
		if (shell->cur_cmd[i]->in_redir_fd != 0)
			dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		if (shell->cur_cmd[i]->out_redir_fd != 1)
			dup2(p2[1], STDOUT_FILENO);
		close(p2[1]);
		if (handle_builtins(shell, i, get_builtin_no(shell->cur_cmd[i]->cmd)))
			exit(g_exit_status);
		c = ms_get_path(p1, p2, shell, i);
		if (execve(c->path, shell->cur_cmd[i]->cmd, c->envp) == -1)
			exit_msg("execve", strerror(errno), EXIT_FAILURE, c);
	}
	close(p1[0]);
	close(p2[1]);
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

// if redirection happened, then we need to close the pipe fds explicitly
static void	redirect_to_pipes(t_cmd_chunk *cmd, int pipes[2][2], int pipe_no)
{
	// printf("in = %d, out = %d\n", cmd->in_redir_fd, cmd->out_redir_fd);
	if (cmd->in_redir_fd > 0)
	{
		dup2(cmd->in_redir_fd, pipes[pipe_no][0]);
		// if (cmd->in_redir_fd != 0)
			close(cmd->in_redir_fd);
	}
	if (cmd->out_redir_fd > 1)
	{
		dup2(cmd->out_redir_fd, pipes[!pipe_no][1]);
		// if (cmd->out_redir_fd != 1)
			close(cmd->out_redir_fd);
	}
}

void	close_pipes_redir(int pipes[2][2], int pipe_no, t_cmd_chunk *cmd)
{
	if (cmd->in_redir_fd >= 0)
		close(pipes[pipe_no][0]);
	if (cmd->out_redir_fd >= 0)
		close(pipes[!pipe_no][1]);
}

int	ms_pipex(t_ms *shell, int cmd_count)
{	
	int			p[2][2];
	int			i;
	int			pipe_no;
	t_cmd_chunk **cmds;

	if (check_err("pipe", pipe(p[0])) == -1)
		return (EXIT_FAILURE);
	close(p[0][1]);
	shell->pids = (int *)malloc(sizeof(int) * (cmd_count));
	pipe_no = 0;
	i = -1;
	cmds = shell->cur_cmd;
	while (cmds[++i])
	{
		if (check_err("pipe", pipe(p[!pipe_no])) == -1)
		{
			free(shell->pids);
			return (EXIT_FAILURE);
		}
		redirect_to_pipes(cmds[i], p, pipe_no);
		if (cmds[i]->in_redir_fd != -1 && cmds[i]->out_redir_fd != -1)
			shell->pids[i] = exec_cmd(p[pipe_no], p[!pipe_no], shell, i);
		else
			shell->pids[i] = -1;
		close_pipes_redir(p, pipe_no, cmds[i]);
		pipe_no = !pipe_no;
	}
	close(p[pipe_no][0]);
	return (wait_cmds(shell, i));
}
