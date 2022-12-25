/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:57:54 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/09 09:57:54 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

int	ft_printf(const char *format, ...);
int	print_var(char format, va_list args);
int	print_char(int c);
int	print_str(void *str);
int	ft_putnbr_base(long long int num, char *base);
int	ft_print_memory(unsigned long long int num);

#endif