/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_fullcmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:28:19 by bammar            #+#    #+#             */
/*   Updated: 2023/01/26 22:19:40 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quotes(char **arr)
{
	int		i;
	char	*temp;

	i = -1;
	while (arr[++i])
	{
		temp = arr[i];
		arr[i] = ft_exclude_quotes(arr[i]);
		free(temp);
	}
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
	cmds = split_with_no_quotes(temp, ' ');
	if (!cmds)
		return (free(temp), NULL);
	*line_piece += cmds_length;
	remove_quotes(cmds);
	return (free(temp), cmds);
}
