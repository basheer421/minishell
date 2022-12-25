/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 21:45:34 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/04 20:50:26 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	has_new_line(char *buf)
{
	int	i;

	if (!buf)
		return (0);
	i = -1;
	while (buf[++i])
		if (buf[i] == '\n')
			return (i + 1);
	return (0);
}

char	*ft_strndup(const char *s, int n)
{
	char	*new_str;
	int		i;

	if (!s || n == 0)
		return (0);
	new_str = malloc((n + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = -1;
	while (++i < n)
		new_str[i] = s[i];
	new_str[i] = 0;
	return (new_str);
}

char	*ft_strnjoin(char **buf, char **new_block)
{
	char	*new_buf;
	int		i;
	int		len1;
	int		len2;

	len1 = ft_strlen(*buf);
	len2 = ft_strlen(*new_block);
	new_buf = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!new_buf)
		return (0);
	i = -1;
	while (++i < len1)
		new_buf[i] = (*buf)[i];
	while (i < len1 + len2)
	{
		new_buf[i] = (*new_block)[i - len1];
		i++;
	}
	new_buf[i] = 0;
	free(*buf);
	free(*new_block);
	return (new_buf);
}

char	*get_line(char **buf, int bytes_read, int line_len)
{
	char	*line;
	char	*reserve;
	int		buf_len;
	int		final_len;

	buf_len = ft_strlen(*buf);
	final_len = buf_len - bytes_read + line_len;
	line = ft_strndup(*buf, final_len);
	reserve = ft_strndup(*buf + final_len, bytes_read - line_len);
	free(*buf);
	*buf = reserve;
	return (line);
}
