/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:37:07 by mfirdous          #+#    #+#             */
/*   Updated: 2023/02/10 18:37:07 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec_cmds(t_ms *shell, int pipe_count)
{
	bool	cmd_is_builtin;

	// printf("start exec\n");
	redirect_input(shell);
	if (g_exit_status == 130)
		return (ms_clean(shell->cur_cmd, NULL, NULL), 0);
	redirect_output(shell->cur_cmd);
	// if (g_exit_status != 0)
		// return (ms_clean(chunks, NULL, NULL), 0);
	cmd_is_builtin = false;
	if (pipe_count == 0)
		cmd_is_builtin = exec_builtin_solo(shell);
	if (pipe_count > 0 || !cmd_is_builtin)
		g_exit_status = ms_pipex(shell, pipe_count + 1);
	return (ms_clean(shell->cur_cmd, NULL, NULL), 0);
}
