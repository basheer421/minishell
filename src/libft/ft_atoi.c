/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:49:30 by bammar            #+#    #+#             */
/*   Updated: 2022/08/14 17:14:38 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	super_bad_case(int sign)
{
	if (sign == 1)
		return (-1);
	else if (sign == -1)
		return (0);
	return (1);
}

static int	bad_case(char *x, int sign, int y, int zrs)
{
	int		i;
	char	*max;

	if (y - zrs > 19)
		return (super_bad_case(sign));
	max = "9223372036854775808";
	if (sign == 1)
		max = "9223372036854775807";
	i = 0;
	while (x[i] != 0)
	{
		if (x[i] > max[i])
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		else if (x[i] < max[i])
			return (1);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			y;
	long long	val;
	int			sign;
	int			zrs;

	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	val = 0;
	y = 0;
	zrs = 0;
	while (str[i + y] != 0 && (str[i + y] >= '0' && str[i + y] <= '9'))
	{
		val = (val * 10) + (str[i + y++] - '0');
		zrs += (val == 0);
	}
	if (y - zrs >= 19 && bad_case((char *)str + i + zrs, sign, y, zrs) != 1)
		return (bad_case((char *)str + i + zrs, sign, y, zrs));
	return (val * sign);
}
