/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_fullcmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:28:19 by bammar            #+#    #+#             */
/*   Updated: 2023/02/25 17:47:43 by mfirdous         ###   ########.fr       */
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

static int	tick_inside_vars(t_inside *inside, char c)
{
	if (c == '\'' && !inside->dquotes)
		inside->quotes = !inside->quotes;
	else if (c == '\"' && !inside->quotes)
		inside->dquotes = !inside->dquotes;
	return (1);
}

static bool	is_end(char c, t_inside *inside)
{
	if (!inside->dquotes && !inside->quotes && (c == 0 || c == '>' || c == '<'))
		return (true);
	return (false);
}

char	**ms_get_fullcmd(char *line_piece, int *ptr)
{
	char		**cmds;
	char		*temp;
	int			cmds_length;
	t_inside	inside;

	if (!line_piece || !line_piece[*ptr])
		return (0);
	cmds_length = 0;
	ft_bzero(&inside, sizeof(t_inside));
	while (!is_end((line_piece + *ptr)[cmds_length], &inside)
		&& *ft_skip_spaces((line_piece + *ptr)))
		cmds_length += tick_inside_vars(&inside,
				(line_piece + *ptr)[cmds_length]);
	if (!ms_contains_cmd((line_piece + *ptr)) || cmds_length == 0)
		return (NULL);
	temp = ft_substr((line_piece + *ptr), 0, cmds_length);
	cmds = split_with_no_quotes(temp, ' ');
	if (!cmds)
		return (free(temp), NULL);
	(*ptr) += cmds_length;
	return (free(temp), remove_quotes(cmds), cmds);
}
