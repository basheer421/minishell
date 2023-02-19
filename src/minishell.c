/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:39:04 by bammar            #+#    #+#             */
/*   Updated: 2023/02/18 18:17:17 by bammar           ###   ########.fr       */
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
	while (1)
	{
		signal(SIGINT, ms_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		shell->cur_cmd = NULL;
		ms_line_read("\033[0;35mpsh\033[0m$ ", shell);
	}
	(void)argc;
	(void)argv;
	// printf("exiting here\n");
	// ms_destroy(shell);
	// clear_history();
	return (0);
}
