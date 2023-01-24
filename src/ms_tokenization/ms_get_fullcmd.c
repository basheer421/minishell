/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_fullcmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:28:19 by bammar            #+#    #+#             */
/*   Updated: 2023/01/25 00:38:44 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increment_string(char **str, int amount)
{
	int	i;

	i = 0;
	while (str[0][i] && i < amount)
		i++;
	*str += i;
}

char	**ms_get_fullcmd(char **line_piece)
{
	char	**cmds;
	char	*temp;
	int		cmds_length;

	if (!*line_piece || !**line_piece)
		return (0);
	cmds_length = 0;
	while (line_piece[0][cmds_length] && line_piece[0][cmds_length] != '>'
		&& line_piece[0][cmds_length] != '<'
		&& *ft_skip_spaces(&(line_piece[0][cmds_length])))
		cmds_length++;
	if (!ms_contains_cmd(line_piece[0]) || cmds_length == 0)
		return (NULL);
	temp = ft_substr(*line_piece, 0, cmds_length);
	if (!temp)
		return (NULL);
	cmds = split_with_no_quotes(temp, ' '); // i should use my split but it's not working
	if (!cmds)
		return (free(temp), NULL);
	*line_piece += cmds_length;
	return (free(temp), cmds);
}
