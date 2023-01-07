/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:20:36 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/03 13:20:36 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_echo(char **strs, bool n_flag)
{
	int	i;

	if (!strs)
		exit(0);
	i = 1;
	if (n_flag)
		i = 2;
	if (strs[i])
		ft_printf("%s", strs[i]);
	if (strs[i])
		while (strs[++i])
			ft_printf(" %s", strs[i]);
	if (!n_flag)
		ft_printf("\n");
}
