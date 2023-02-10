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

bool	is_n_flag(char *arg)
{
	int	i;

	if (!arg)
		return (false);
	i = 0;
	if (arg[0] != '-')
		return (false);
	while (arg[++i])
		if (arg[i] != 'n')
			return (false);
	return (true);
}

/**
 * @brief Runs the echo command on the given strings
 * @param strs array of strings to be output on the screen
 */
int	ms_echo(char **strs)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = false;
	if (!strs)
		return (EXIT_FAILURE);
	while (strs[++i])
	{
		if (!is_n_flag(strs[i]))
			break;
		n_flag = true;
	}
	if (strs[i])
	{
		ft_printf("%s", strs[i]);
		while (strs[++i])
			ft_printf(" %s", strs[i]);
	}
	if (!n_flag)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
