/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_contains_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:28:54 by bammar            #+#    #+#             */
/*   Updated: 2022/12/25 22:35:47 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ofcourse not done lol
bool	ms_line_contains_commands(char *line)
{
	size_t	length;

	length = ft_strlen(line);
	if (length != 4)
		return (0);
	return (ft_strncmp(line, "exit", 4) == 0);
}
