/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:02:22 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/24 00:18:29 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sigint_handler(int sig)
{
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
	(void)sig;

	// int	ret;

	// ret = waitpid(-1, NULL, WNOHANG);
	// if (sig == SIGINT && ret == -1)
	// {
	// 	write(2, "\n", 1);
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// 	g_exit_status = 130;
	// }
}

void	ms_sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
		;
}