/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:51:36 by bammar            #+#    #+#             */
/*   Updated: 2022/08/14 16:30:54 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	y;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	i = 0;
	while (dst[i] != 0)
		i++;
	y = 0;
	while (i + 1 < dstsize && src[y] != 0)
		dst[i++] = src[y++];
	if (i < dstsize)
		dst[i] = 0;
	while (src[y++] != 0)
		i++;
	return (i);
}
