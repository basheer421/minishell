/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:33:48 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/06 18:33:48 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(t_ms *shell)
{
	char	cur_dir[MAXPATHLEN];
	char	*pwd;

	if (!getcwd(cur_dir, MAXPATHLEN))
	{
		pwd = (char *)ht_get(shell->env_vars, "PWD");
		if (!pwd)
			return (EXIT_FAILURE);
		printf("%s\n", pwd);
		return (EXIT_SUCCESS);
	}
	printf("%s\n", cur_dir);
	return (EXIT_SUCCESS);
}
