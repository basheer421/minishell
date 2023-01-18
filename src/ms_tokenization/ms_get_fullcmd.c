/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_fullcmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:28:19 by bammar            #+#    #+#             */
/*   Updated: 2023/01/18 17:01:18 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// REMEMBER TO CHECK FOR commad not found ERROR
char	**ms_get_fullcmd(char *line_piece,
						t_command_chunk *chunk)
{
	char	**cmds;
	char	*temp;
	int		cmds_length;

	if (!*line_piece || !*line_piece)
		return (0);
	cmds_length = 0;
	while (line_piece[cmds_length] && line_piece[cmds_length] != '>'
		&& line_piece[cmds_length] != '<'
		&& *ft_skip_spaces(&line_piece[cmds_length]))
		cmds_length++;
	if (!ms_contains_cmd(line_piece) || cmds_length == 0)
		return (NULL);
	temp = ft_substr(line_piece, 0, cmds_length);
	if (!temp)
		return (NULL);
	cmds = split_with_no_quotes(temp, ' ');
	if (!cmds)
		return (free(temp), NULL);
	line_piece += ft_strlen(temp);
	chunk->cmd = cmds;
	return (free(temp), cmds);
}
