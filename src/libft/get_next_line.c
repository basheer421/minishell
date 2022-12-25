/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 21:42:21 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/04 20:30:42 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_block(int fd, char **block)
{
	int	bytes_read;

	*block = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!(*block))
		return (0);
	bytes_read = read(fd, *block, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(*block);
		*block = 0;
	}
	else
		(*block)[bytes_read] = 0;
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*new_block;
	int			bytes_read;
	int			line_len;

	if (!buf || !buf[0])
		bytes_read = read_block(fd, &buf);
	else
		bytes_read = ft_strlen(buf);
	line_len = has_new_line(buf);
	while (line_len == 0 && bytes_read > 0)
	{
		bytes_read = read_block(fd, &new_block);
		line_len = has_new_line(new_block);
		buf = ft_strnjoin(&buf, &new_block);
	}
	if (bytes_read <= 0 && !buf)
		return (0);
	return (get_line(&buf, bytes_read, line_len));
}
