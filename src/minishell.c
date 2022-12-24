/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:39:04 by bammar            #+#    #+#             */
/*   Updated: 2022/12/24 23:28:59 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *line;

	while (1)
	{
		line = ms_line_read("minishell$ ");
		printf("%s\n", line);
		if (ft_strcmp(line, "exit") == 0)
			break ;
	}
	(void)argc;
	(void)argv;
	(void)envp;
	free(line);
	return (0);
}