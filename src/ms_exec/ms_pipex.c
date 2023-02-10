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

static int	exec_cmd(int p1[], int p2[], char **cmd, t_ms *shell)
{
	int			pid;
	t_alloced	*c;

	pid = check_err("fork", fork());
	if (pid == 0)
	{
		close(p2[0]);
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		dup2(p2[1], STDOUT_FILENO);
		close(p2[1]);
		if (handle_builtins(cmd, shell, get_builtin_no(cmd)))
			exit(g_exit_status);
		c = ms_get_path(p1, p2, cmd, shell);
		check_err("execve", execve(c->path, cmd, c->envp));
	}
	close(p1[0]);
	close(p2[1]);
	return (pid);
}

static int	wait_cmds(int *pids, int count)
{
	int	i;
	int	status;

	i = -1;
	while (++i < count)
		waitpid(pids[i], &status, 0);
	free(pids);
	if (WIFSIGNALED(status))
		return (ms_get_sig_status(WTERMSIG(status)));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static void	redirect_to_pipes(t_cmd_chunk *cmd, int pipes[2][2], int pipe_no)
{
	// printf("in = %d, out = %d\n", cmd->in_redir_fd, cmd->out_redir_fd);
	if (cmd->in_redir_fd >= 0)
	{
		dup2(cmd->in_redir_fd, pipes[pipe_no][0]);
		if (cmd->in_redir_fd != 0)
			close(cmd->in_redir_fd);
	}
	if (cmd->out_redir_fd >= 0)
	{
		dup2(cmd->out_redir_fd, pipes[!pipe_no][1]);
		if (cmd->out_redir_fd != 1)
			close(cmd->out_redir_fd);
	}
}

int	ms_pipex(t_cmd_chunk **cmds, int cmd_count, t_ms *shell)
{	
	int		p[2][2];
	int		*pids;
	int		i;
	int		pipe_no;

	check_err("pipe", pipe(p[0]));
	close(p[0][1]);
	pids = (int *)malloc(sizeof(int) * (cmd_count));
	pipe_no = 0;
	i = -1;
	while (cmds[++i])
	{
		check_err("pipe", pipe(p[!pipe_no]));
		redirect_to_pipes(cmds[i], p, pipe_no);
		pids[i] = exec_cmd(p[pipe_no], p[!pipe_no], cmds[i]->cmd, shell);
		pipe_no = !pipe_no;
	}
	close(p[pipe_no][0]);
	return (wait_cmds(pids, i));
}
