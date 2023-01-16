/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_contains_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:06:42 by bammar            #+#    #+#             */
/*   Updated: 2023/01/07 18:49:16 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_contains_output(char *line_chunk)
{
	if (!line_chunk || !*line_chunk)
		return (false);
	if (*(ft_skip_spaces(line_chunk)) == '>')
		return (true);
	return (false);
}