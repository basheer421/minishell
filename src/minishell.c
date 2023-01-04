/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:39:04 by bammar            #+#    #+#             */
/*   Updated: 2023/01/03 18:38:49 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	*shell;

	shell = ms_init(envp);
	if (!shell)
		return (1);
	while (shell->error_code != -1)
	{
		shell->error_code = ms_line_read("minishell$ ", shell);
		// print_error_function_here
	}
	printf("%s\n", (char *)ht_get(shell->env_vars, "PATH"));
	(void)argc;
	(void)argv;
	(void)envp;
	ms_destroy(shell);
	return (0);
}
