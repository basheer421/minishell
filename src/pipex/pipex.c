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

int	exec_cmd(int p1[], int p2[], char **cmd, t_ms *shell)
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
		if (handle_builtins(cmd, shell))
			exit(g_exit_status);
		c = check_cmd_path(p1, p2, cmd, shell);
		check_err("execve", execve(c->path, cmd, c->envp));
	}
	close(p1[0]);
	close(p2[1]);
	return (pid);
}

int	wait_cmds(int *pids, int count)
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

// for now uses stdin for first command and stdout for last command
int	pipex(t_cmd_chunk **chunks, int cmd_count, t_ms *shell)
{	
	int		pipes[2][2];
	int		*pids;
	int		i;
	int		pipe_no;

	check_err("pipe", pipe(pipes[0]));
	close(pipes[0][1]);
	pids = (int *)malloc(sizeof(int) * (cmd_count));
	pipe_no = 0;
	i = -1;
	// dup2(STDIN_FILENO, pipes[0][0]);					// will remove later

	redirect_input(chunks);
	redirect_output(chunks);
	while (chunks[++i])
	{
		check_err("pipe", pipe(pipes[!pipe_no]));
		if (chunks[i]->in_redir_fd >= 0)
		{
			dup2(chunks[i]->in_redir_fd, pipes[pipe_no][0]);
			if (chunks[i]->in_redir_fd != 0)
				close(chunks[i]->in_redir_fd);
		}
		if (chunks[i]->out_redir_fd >= 0)
		{
			dup2(chunks[i]->out_redir_fd, pipes[!pipe_no][1]);
			if (chunks[i]->out_redir_fd != 1)
				close(chunks[i]->out_redir_fd);
		}

		// if (!redirect_input(chunks[i]->inputs, pipes[pipe_no], (i == 0)) || \
		// 	!redirect_output(chunks[i]->outputs, pipes[!pipe_no], (i == cmd_count - 1)))
		// {
		// 	printf("redirect error\n");
		// 	return (1); // redirect error 
		// }
		
		// if (!chunks[i + 1])								// will remove later
			// dup2(STDOUT_FILENO, pipes[!pipe_no][1]); 	// because chunks->input and chunks->output will be used instead
		
		pids[i] = exec_cmd(pipes[pipe_no], pipes[!pipe_no], chunks[i]->cmd, shell);
		pipe_no = !pipe_no;
	}
	close(pipes[pipe_no][0]);
	return (wait_cmds(pids, i));
	return (0);
}
