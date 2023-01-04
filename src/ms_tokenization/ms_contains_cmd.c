/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_contains_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:59:26 by bammar            #+#    #+#             */
/*   Updated: 2023/01/04 19:16:31 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_contains_cmd(char *line_chunk)
{
	if (ms_contains_input(line_chunk))
		return (false);
	if (ms_contains_output(line_chunk))
		return (false);
	if (!(*ft_skip_spaces(line_chunk)))
		return (false);
	return (false);
}
