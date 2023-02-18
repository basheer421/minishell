/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:47:48 by bammar            #+#    #+#             */
/*   Updated: 2023/02/18 18:53:18 by bammar           ###   ########.fr       */
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

void	ms_add_spaces(char **line)
{
	int			i;
	t_inside	inside;

	ft_bzero(&inside, sizeof(t_inside));
	i = -1;
	while ((*line)[++i])
	{
		tick_inside_vars(&inside, (*line)[i]);
		if (ft_is_space((*line)[i]))
			(*line)[i] = ' ';
	}
}
