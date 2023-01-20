/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_run.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:47:09 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/08 17:47:09 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	exec_cmd(char *cmd_str, t_ms *shell)
// {
// 	int		pid;
// 	// t_alloced	*c;
// 	char	*file_path;
// 	char	**cmd_args;

// 	pid = check_err("fork", fork());
// 	if (pid == 0)
// 	{	
// 		close(p2[0]);
// 		c = check_cmd_path(p1, p2, cmd_str, envp);
// 		dup2(p1[0], STDIN_FILENO);
// 		close(p1[0]);
// 		dup2(p2[1], STDOUT_FILENO);
// 		close(p2[1]);
// 		check_err("execve", execve(c->path, c->cmd, envp));
// 	}
// 	return (pid);
// }

int	check_err(char *func_name, int ret_value)
{
	if (ret_value == -1)
		perror(func_name);
	return (ret_value);
}

void	set_up_pipes(t_cmd_chunk **chunks, )
{
	int	i;
	int	pipe_no;
	int	pipes[2][2];
	int	*pids;

	i = -1;
	check_err("minishell: pipe: ", pipe(pipes[0]));
	close(pipes[0][1]);
	pipe_no = 0;
	while (chunks[++i])
	{
		check_err("minishell: pipe: ", pipe(pipes[!pipe_no]));
		pipe_no = !pipe_no;
	}
}
