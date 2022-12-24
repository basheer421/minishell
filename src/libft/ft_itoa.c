/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:16:50 by bammar            #+#    #+#             */
/*   Updated: 2022/08/14 16:38:02 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*min_itoa(void)
{
	char	*str;

	str = malloc(12);
	if (!str)
		return (NULL);
	ft_memcpy(str, "-2147483648", 12);
	return (str);
}

static	char	*reverse(char *str)
{
	int		len;
	int		i;
	char	temp;
	char	*s;

	s = str;
	len = 0;
	while (s[len] != 0)
		len++;
	i = 0;
	while (i < len / 2)
	{
		temp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = temp;
		i++;
	}
	return (s);
}

static int	intlen(int n)
{
	if (n < 10)
		return (1);
	if (n < 100)
		return (2);
	if (n < 1000)
		return (3);
	if (n < 10000)
		return (4);
	if (n < 100000)
		return (5);
	if (n < 1000000)
		return (6);
	if (n < 10000000)
		return (7);
	if (n < 100000000)
		return (8);
	if (n < 1000000000)
		return (9);
	return (10);
}

char	*ft_itoa(int n)
{
	int		nb;
	int		i;
	int		len;
	char	*str;

	if (n == -2147483648)
		return (min_itoa());
	nb = (n);
	if (n < 0)
		nb *= -1;
	len = intlen(nb);
	str = malloc(len + 1 + (n < 0));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i++] = '0' + (nb % 10);
		nb = nb / 10;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = 0;
	str = reverse(str);
	return (str);
}
