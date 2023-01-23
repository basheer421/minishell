/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:31:22 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/21 14:41:17 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_clean(t_command_chunk **chunks, char **string_chunks, char *line)
{
	int	i;

	i = -1;
	while (chunks[++i])
	{
		ft_split_destroy(chunks[i]->cmd);
		free(chunks[i]);
	}
	free(chunks);
	ft_split_destroy(string_chunks);
	if (line)
		free(line);
}
