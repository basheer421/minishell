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

	i = 0;
	if (arg_count > 1)
		while(strs[++i])
			ht_remove(shell->env_vars, strs[i]);
	return (EXIT_SUCCESS);
}
