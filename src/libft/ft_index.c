/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:54:23 by bammar            #+#    #+#             */
/*   Updated: 2023/01/08 21:57:27 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_index(const char *str, int c)
{
	int	i;
	
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}