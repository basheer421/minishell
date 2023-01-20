/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_input_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 21:46:05 by bammar            #+#    #+#             */
/*   Updated: 2023/01/20 18:39:09 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_get_input_fd(char *line_piece, t_cmd_chunk *chunk)
{
	char	*input;
	char	*temp;

	if (!ms_contains_input(line_piece))
		chunk->input_fd = -2;
	input = NULL;
	while (ms_contains_input(line_piece))
	{
		if (input)
			free(input);
		input = ms_get_next_input(line_piece);
		if (access(input, F_OK) != 0)
			return (-1);
		chunk->input_fd = open(input, O_RDONLY);
		if (chunk->input_fd < 0)
			return (-1);
		temp = line_piece;
		line_piece = ft_strdup(line_piece + ft_strlen(input));
		free(temp);
		if (!line_piece)
			return (-1);
	}
	return (chunk->input_fd);
}
