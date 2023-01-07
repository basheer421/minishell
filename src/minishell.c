/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:39:04 by bammar            #+#    #+#             */
/*   Updated: 2023/01/04 15:23:46 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	*shell;

	shell = ms_init(envp);
	if (!shell)
		return (1);
	while (1)
	{
		shell->error_code = ms_line_read("\033[0;35mminishell\033[0m$ ", shell);
		// print_error_function_here
	}
	printf("%s\n", (char *)ht_get(shell->env_vars, "PATH"));
	(void)argc;
	(void)argv;
	(void)envp;
	
	ms_destroy(shell);
	return (0);
}
