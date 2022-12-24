/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:35:30 by bammar            #+#    #+#             */
/*   Updated: 2022/08/14 17:21:42 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (d > s && i < n)
		i++;
	while (i > 0)
	{
		d[i - 1] = s[i - 1];
		i--;
	}
	while (d < s && i < n)
	{
		if (d[i] != s[i])
			d[i] = s[i];
		i++;
	}
	return ((void *)d);
}
