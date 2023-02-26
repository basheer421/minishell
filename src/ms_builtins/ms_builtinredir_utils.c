/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtinredir_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:41:56 by mfirdous          #+#    #+#             */
/*   Updated: 2023/02/26 17:48:18 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdinout(t_cmd_chunk *cmd_info, int og_stdin, int og_stdout)
{
	if (cmd_info->in_fd > 0)
	{
		dup2(og_stdin, STDIN_FILENO);
		close(og_stdin);
	}
	if (cmd_info->out_fd > 1)
	{
		dup2(og_stdout, STDOUT_FILENO);
		close(og_stdout);
	}
}

void	redir_stdinout(t_cmd_chunk *cmd_info, int *og_stdin, int *og_stdout)
{
	if (cmd_info->in_fd > 0)
	{
		*og_stdin = dup(STDIN_FILENO);
		dup2(cmd_info->in_fd, STDIN_FILENO);
		close(cmd_info->in_fd);
	}
	if (cmd_info->out_fd > 1)
	{
		*og_stdout = dup(STDOUT_FILENO);
		dup2(cmd_info->out_fd, STDOUT_FILENO);
		close(cmd_info->out_fd);
	}
}
