/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_with_no_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:18:11 by bammar            #+#    #+#             */
/*   Updated: 2023/01/20 15:36:17 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_split
{
	char		*line;
	char		c;
	char		**content;
	int			*positions;
	size_t		content_size;
}				t_split_vars;

static size_t	get_length(char *line, char *start_pos, int next_c)
{
	if (next_c == -1)
		return (ft_strlen(start_pos));
	return (ft_strlen(start_pos) - ft_strlen(line + next_c));
}

static bool	fill_content(t_split_vars *vars)
{
	size_t	i;
	int		current_index;
	char	*start_pos;

	i = 0;
	current_index = 0;
	while (i < vars->content_size)
	{
		start_pos = chrskip(vars->line + current_index, vars->c);
		if (!start_pos || !*start_pos)
			return (free(vars->positions), free(vars->content), false);
		vars->content[i] = ft_substr(start_pos, 0, get_length(vars->line,
					start_pos, vars->positions[i]));
		if (!vars->content[i])
			return (free(vars->positions), free(vars->content), false);
		current_index = vars->positions[i++] + 1;
	}
	vars->content[vars->content_size] = NULL;
	return (true);
}

char	**split_with_no_quotes(char *line, int c)
{
	t_split_vars	vars;

	while (*line == c)
		line++;
	if (!line || !*line)
		return (NULL);
	vars.c = c;
	vars.line = line;
	vars.content_size = split_with_no_quotes_len(line, c) + 1;
	vars.positions = ms_char_positions(line, c);
	if (!vars.positions)
		return (NULL);
	vars.content = ft_malloc(sizeof(char *) * (vars.content_size + 1));
	if (!fill_content(&vars))
		return (NULL);
	return (free(vars.positions), vars.content);
}
