/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:39:04 by bammar            #+#    #+#             */
/*   Updated: 2023/01/24 00:35:55 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_ms	*shell;

	shell = ms_init(envp);
	if (!shell)
		return (1);
	while (shell->error_code != -1)
	{
		signal(SIGINT, ms_sigint_handler);
		signal(SIGQUIT, ms_sigquit_handler);
		ms_line_read("\033[0;35mminishell\033[0m$ ", shell);
	}
	(void)argc;
	(void)argv;
	ms_destroy(shell);
	clear_history();
	return (0);
}
