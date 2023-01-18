/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_nonalnum.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:55:47 by bammar            #+#    #+#             */
/*   Updated: 2023/01/18 16:56:07 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_next_nonalnum(char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}
