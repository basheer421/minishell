/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:56:47 by bammar            #+#    #+#             */
/*   Updated: 2022/08/14 16:31:46 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;
	int		slen;

	slen = 0;
	while (s[slen] != 0)
		slen++;
	if (c == 0)
		return ((char *)s + slen);
	i = 0;
	ptr = NULL;
	while (s[i] != 0)
		if (s[i++] == (char)c)
			ptr = (char *)s + i - 1;
	return (ptr);
}
