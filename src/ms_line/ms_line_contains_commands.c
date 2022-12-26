/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_contains_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:28:54 by bammar            #+#    #+#             */
/*   Updated: 2022/12/26 21:56:34 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ofcourse not done lol
bool	ms_line_contains_commands(char *line, t_ms *shell)
{
	size_t	length;

	(void)shell;
	printf("pipe_count: %zu\n", ms_pipes_count(line));
	length = ft_strlen(line);
	if (length != 4)
		return (1);
	return (ft_strncmp(line, "exit", 4) != 0);
}
