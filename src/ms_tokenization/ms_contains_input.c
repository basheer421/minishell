/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_contains_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:58:44 by bammar            #+#    #+#             */
/*   Updated: 2023/01/04 17:04:06 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_contains_input(char *line_chunk)
{
	if (!line_chunk || !*line_chunk)
		return (false);
	if (*(ft_skip_spaces(line_chunk)) == '<')
		return (true);
	return (false);
}
