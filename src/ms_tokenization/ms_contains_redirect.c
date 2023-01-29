/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_contains_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:58:44 by bammar            #+#    #+#             */
/*   Updated: 2023/01/24 02:16:06 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_contains_redirect(char *line_chunk, char type)
{
	if (!line_chunk || !*line_chunk)
		return (false);
	if (*(ft_skip_spaces(line_chunk)) == type)
		return (true);
	return (false);
}
