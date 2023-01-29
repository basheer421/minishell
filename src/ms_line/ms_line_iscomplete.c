/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_iscomplete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:47:00 by bammar            #+#    #+#             */
/*   Updated: 2023/01/28 18:30:32 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tick_inside_vars(t_inside *inside, char c)
{
	if (c == '\'' && !inside->dquotes)
		inside->quotes = !inside->quotes;
	else if (c == '\"' && !inside->quotes)
		inside->dquotes = !inside->dquotes;
}

// static bool	contains_mutlipipes(char *line)
// {
// 	t_inside	inside;
// 	int			i;

// 	ft_bzero(&inside, sizeof(t_inside));
// 	i = -1;
// 	while (line[++i])
// 	{
// 		tick_inside_vars(&inside, line[i]);
// 		if (line[i] == '|' && line[i + 1] == '|'
// 			&& !inside.quotes && !inside.dquotes)
// 			return (true);
// 	}
// 	return (false);
// }

static bool	unclosed_token(char *line)
{
	t_inside	inside;
	bool		inpipe;
	int			i;

	ft_bzero(&inside, sizeof(t_inside));
	inpipe = false;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|' && inpipe && !inside.dquotes && !inside.quotes)
			return (true);
		else if (line[i] == '|' && !inpipe && !inside.dquotes && !inside.quotes)
			inpipe = true;
		else if (line[i] != '|' && !ft_is_space(line[i])
			&& inpipe && !inside.dquotes && !inside.quotes)
			inpipe = false;
		tick_inside_vars(&inside, line[i]);
	}
	return (inside.quotes || inside.dquotes || inpipe);
}

// static bool	contains_empty_str(char *line)
// {
// 	int	i;

// 	i = -1;
// 	while (line[++i])
// 	{
// 		if (!*ft_skip_spaces(str_chunks[i]))
// 			return (true);
// 	}
// 	return (false);
// }

bool	ms_line_iscomplete(char *line)
{
	char	*nline;

	nline = ft_strtrim(line, " ");
	if (!nline)
		return (false);
	if (!*nline || nline[0] == '|'
		|| nline[ft_strlen(nline) - 1] == '|'
		|| unclosed_token(nline))
	{
		g_exit_status = UNEXPECTED_TOKEN;
		return (perror("syntax error, unexpected token"),
			free(nline), false);
	}
	return (free(nline), true);
}
