/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_input_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 21:46:05 by bammar            #+#    #+#             */
/*   Updated: 2023/01/21 15:34:40 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_get_input_fd(char *line_piece, t_command_chunk *chunk)
{
	char		*input;
	struct stat	info;

	while (ms_contains_input(line_piece))
	{
		if (chunk->input_fd != 0)
			close(chunk->input_fd);
		input = ms_get_next_input(&line_piece);
		if (access(input, F_OK) != 0)
			return (free(input),
				ms_errno_check(ft_strjoin(input, ": No such file or directory"), -1)); // file not found
		else if ((stat(input, &info) < 0 || !(info.st_mode & S_IRUSR)))	
				return (free(input), ms_errno_check(ft_strjoin(input, ": Permission denied"), -1));
		chunk->input_fd = open(input, O_RDONLY);
		if (chunk->input_fd < 0)
			return (free(input), -1);
		free(input);
	}
	return (chunk->input_fd);
}