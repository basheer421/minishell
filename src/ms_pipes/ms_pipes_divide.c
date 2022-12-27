/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes_divide.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:34:19 by bammar            #+#    #+#             */
/*   Updated: 2022/12/27 23:07:00 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	bool	inside_quotes;
	bool	inside_dquotes;
	int		i;
	int		word_num;
	char	**content;
}			t_vars;

static bool	is_pipe(char *line, t_vars vars)
{
	if (line[vars.i] == '|' && !vars.inside_quotes && !vars.inside_dquotes
		&& line[vars.i + 1] != '|')
		if (vars.i == 0 || (vars.i != 0 && line[vars.i - 1] != '|'))
			return (true);
	return (false);
}

// // to be implemented
// static bool	is_operand(void)
// {
// 	return (false);
// }

// // to be implemented
// static char	**content_init(char *line)
// {
// 	char	**content;
// 	size_t	size;

// 	size = ms_pipes_count(line) + 1;
// 	content = malloc(sizeof(char *) * (size + 1));
// 	if (!content)
// 		return (NULL);
// 	while (size > 0)
// 	{
// 		if (line == )
// 	}
// }

char	**ms_pipes_divide(char *line)
{
	t_vars	vars;

	vars.inside_quotes = false;
	vars.inside_dquotes = false;
	vars.content = malloc(sizeof(char *) * (ms_pipes_count(line) + 2));
	if (!vars.content)
		return (NULL);
	vars.i = -1;
	vars.word_num = 0;
	while (line[++vars.i])
	{
		if (line[vars.i] == '\"')
			vars.inside_dquotes = !vars.inside_dquotes;
		else if (line[vars.i] == '\'')
			vars.inside_quotes = !vars.inside_quotes;
		else if (is_pipe(line, vars) || is_operand())
			vars.word_num++;
	}
	vars.content[vars.word_num] = NULL;
	return (vars.content);
}
