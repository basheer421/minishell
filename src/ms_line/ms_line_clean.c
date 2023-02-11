/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:31:22 by mfirdous          #+#    #+#             */
/*   Updated: 2023/02/11 14:17:14 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_file_destroy(void *file)
{
	t_file	file_cpy;

	if (!file)
		return ;
	ft_memcpy(&file_cpy, file, sizeof(t_file));
	free(file_cpy.name);
	free(file);
}

void	ms_clean(t_cmd_chunk **chunks, char **string_chunks, char *line)
{
	int	i;

	if (chunks)
	{
		i = -1;
		while (chunks[++i])
		{
			ft_split_destroy(chunks[i]->cmd);
			ft_lstclear(&(chunks[i]->inputs), t_file_destroy);
			ft_lstclear(&(chunks[i]->outputs), t_file_destroy);
			if (chunks[i]->in_redir_fd > 0)
				close (chunks[i]->in_redir_fd);
			if (chunks[i]->out_redir_fd > 1)
				close (chunks[i]->out_redir_fd);
			free(chunks[i]);
		}
		free(chunks);
	}
	if (string_chunks)
		ft_split_destroy(string_chunks);
	if (line)
		free(line);
}
