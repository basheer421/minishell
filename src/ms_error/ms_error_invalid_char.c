/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_invalid_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:02:43 by bammar            #+#    #+#             */
/*   Updated: 2023/01/08 12:19:44 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_error_invalid_char(char *line)
{
	int		i;
	bool	inside_quotes;
	bool	inside_dquotes;

	inside_quotes = false;
	inside_dquotes = false;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
			inside_quotes = !inside_quotes;
		else if (line[i] == '\"')
			inside_dquotes = !inside_dquotes;
		else if (!inside_quotes && !inside_dquotes 
			&& (line[i] == '\\' || line[i] == ';'))
			return (127); // OR PRINT ERROR
	}
	return (0);
}
