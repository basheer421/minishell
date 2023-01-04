/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_isempty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:45:36 by bammar            #+#    #+#             */
/*   Updated: 2023/01/03 16:46:49 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_line_isempty(char *line)
{
	if (*ft_skip_spaces(line) == 0)
		return (true);
	return (false);
}
