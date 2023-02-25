/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:39:01 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/11 19:39:01 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_unset(t_ms *shell, char **strs, int arg_count)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = EXIT_SUCCESS;
	if (arg_count > 1)
	{
		while (strs[++i])
		{
			if (!ms_is_valid_identifier(strs[i], "unset"))
				exit_status = EXIT_FAILURE;
			else
				ht_remove(shell->env_vars, strs[i]);
		}
	}
	return (exit_status);
}
