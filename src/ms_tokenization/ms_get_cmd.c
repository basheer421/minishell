/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:14:02 by bammar            #+#    #+#             */
/*   Updated: 2023/01/18 17:02:06 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_cmd(char *line_chunk)
{
	char	*cmd;
	char	*line;
	int		len;
	int		i;

	if (!line_chunk)
		return (NULL);
	line = ft_skip_spaces(line_chunk);
	if (!line || !*line)
		return (NULL);
	len = 0;
	while (line[len] && line[len] != '>' && line[len] != '<')
		len++;
	cmd = malloc(len + 1);
	if (!cmd)
		return (NULL);
	i = -1;
	while (++i < len)
		cmd[i] = line[i];
	cmd[i] = 0;
	return (cmd);
}
