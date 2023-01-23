/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_output_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:33:53 by bammar            #+#    #+#             */
/*   Updated: 2023/01/23 21:30:52 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_get_output_fd(char *line_piece, t_cmd_chunk *chunk)
{
	char		*output;
	struct stat	info;

	while (ms_contains_output(line_piece))
	{
		if (chunk->output_fd != 1)
			close(chunk->output_fd);
		output = ms_get_next_output(&line_piece);
		ft_printf("out: %s\n", output);
		if (access(output, F_OK) == 0 
			&& (stat(output, &info) < 0 || !(info.st_mode & S_IWUSR)))
			// permission denied	
				return (/*DO ERROR PRINT HERE*/ free(output), -1);
		chunk->output_fd = open(output, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (chunk->output_fd < 0)
			return (free(output), -1);
		free(output);
	}
	return (chunk->output_fd);
}