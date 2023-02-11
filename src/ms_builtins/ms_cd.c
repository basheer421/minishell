/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 23:44:40 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/07 23:44:40 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*set_new_dir(t_ms *sh, int arg_count, char **path)
{
	char	*new_dir;

	if (arg_count == 1)
	{
		new_dir = (char *)ht_get(sh->env_vars, "HOME");
		if (!new_dir)
			printf("cd: HOME not set\n");
	}
	else if (path[1] && path[1][0] == '-')
	{
		new_dir = (char *)ht_get(sh->env_vars, "OLDPWD");
		if (!new_dir)
			printf("cd: OLDPWD not set\n");
	}
	else
		new_dir = path[1];
	return (new_dir);
}

// returns status as 1 in case of error
int	ms_cd(t_ms *shell, char **path, int arg_count)
{
	char	cur_dir[MAXPATHLEN];
	char	*new_dir;
	char	*pwd;

	new_dir = set_new_dir(shell, arg_count, path);
	if (new_dir && ms_errno_check(ft_strjoin("cd: ", new_dir), \
										chdir(new_dir)) != -1)
	{
		pwd = (char *)ht_get(shell->env_vars, "PWD");
		if (pwd)
		{
			if (ht_contains(shell->env_vars, "OLDPWD"))
				ht_replace(shell->env_vars, "OLDPWD", pwd);
			else
				ht_set(shell->env_vars, "OLDPWD", pwd);
		}
		else
			ht_replace(shell->env_vars, "OLDPWD", "");
		ht_replace(shell->env_vars, "PWD", getcwd(cur_dir, MAXPATHLEN));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/**
 * @test for PWD and OLDPWD
 * when PWD and OLDPWD are unset, do nothing
 * when PWD is unset and we're changing dir, OLDPWD should be set to an empty string
 * when PWD is set but OLDPWD is unset, OLDPWD must be automatically recreated on cd
 */