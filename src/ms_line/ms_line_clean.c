/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:31:22 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/18 19:52:31 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_clean(t_command_chunk **chunks, char **string_chunks, char *line)
{
	int	i;

	i = -1;
	while (chunks[++i])
		free(chunks[i]);
	free(chunks);
	ft_split_destroy(string_chunks);
	free(line);
}
