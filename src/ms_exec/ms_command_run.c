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

int	exec_cmd(char *cmd_str, t_ms *shell)
{
	int		pid;
	// t_alloced	*c;
	char	*file_path;
	char	**cmd_args;
	
	pid = check_err("fork", fork());
	if (pid == 0)
	{	
		close(p2[0]);
		c = check_cmd(p1, p2, cmd_str, envp);
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		dup2(p2[1], STDOUT_FILENO);
		close(p2[1]);
		check_err("execve", execve(c->path, c->cmd, envp));
	}
	return (pid);
}
