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

int	ms_exec_cmds(t_cmd_chunk **chunks, int pipe_count, t_ms *shell)
{
	bool	cmd_is_builtin;

	redirect_input(chunks);
	if (g_exit_status == 130)
		return (ms_clean(chunks, NULL, NULL), 0);
	redirect_output(chunks);
	// if (g_exit_status != 0)
		// return (ms_clean(chunks, NULL, NULL), 0);
	cmd_is_builtin = false;
	if (pipe_count == 0)
		cmd_is_builtin = exec_builtin_solo(chunks[0], shell);
	if (pipe_count > 0 || !cmd_is_builtin)
		g_exit_status = ms_pipex(chunks, pipe_count + 1, shell);
	return (ms_clean(chunks, NULL, NULL), 0);
}
