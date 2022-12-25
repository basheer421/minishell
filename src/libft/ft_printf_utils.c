/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:49:30 by mfirdous          #+#    #+#             */
/*   Updated: 2022/09/01 12:49:30 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_var(char format, va_list ap)
{
	if (format == 'c')
		return (print_char(va_arg(ap, int)));
	if (format == 's')
		return (print_str(va_arg(ap, void *)));
	if (format == 'p')
		return (ft_print_memory(va_arg(ap, unsigned long long int)));
	if (format == 'd' || format == 'i')
		return (ft_putnbr_base(va_arg(ap, int), "0123456789"));
	if (format == 'u')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789"));
	if (format == 'x')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef"));
	if (format == 'X')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF"));
	if (format == '%')
		return (print_char('%'));
	return (0);
}

int	print_char(int c)
{
	return (write(1, &c, 1));
}

int	print_str(void *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int	ft_putnbr_base(long long int num, char *base)
{
	char			s_num[16];
	long long int	radix;
	int				num_len;
	int				i;

	i = 0;
	num_len = 0;
	radix = ft_strlen(base);
	if (num < 0)
	{
		num_len += write(1, "-", 1);
		num = -num;
	}
	while (num > radix - 1)
	{
		s_num[i++] = base[num % radix];
		num /= radix;
	}
	s_num[i++] = base[num];
	while (i)
		num_len += write(1, &s_num[--i], 1);
	return (num_len);
}

int	ft_print_memory(unsigned long long int num)
{
	char	s_num[16];
	char	base[17];
	int		num_len;
	int		i;

	i = 0;
	num_len = 0;
	num_len += write(1, "0x", 2);
	ft_strlcpy(base, "0123456789abcdef", 17);
	while (num > 15)
	{
		s_num[i++] = base[num % 16];
		num /= 16;
	}
	s_num[i++] = base[num];
	while (i)
		num_len += write(1, &s_num[--i], 1);
	return (num_len);
}
