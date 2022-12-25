/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:57:05 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/09 09:57:05 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int		i;
	char	format;
	int		len;
	va_list	ap;

	i = -1;
	len = 0;
	va_start(ap, s);
	while (s[++i])
	{
		if (s[i] == '%')
		{
			format = s[++i];
			len += print_var(format, ap);
		}
		else
			len += write(1, &s[i], 1);
	}
	va_end(ap);
	return (len);
}
