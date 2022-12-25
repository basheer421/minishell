/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:39:04 by bammar            #+#    #+#             */
/*   Updated: 2022/12/25 17:25:16 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *line;

	while (1)
	{
		line = ms_line_read("minishell$ ");
		ft_printf("%s\n", line);
		if (ft_strncmp(line, "exit", 4) == 0)
			break ;
	}
	(void)argc;
	(void)argv;
	(void)envp;
	free(line);
	return (0);
}