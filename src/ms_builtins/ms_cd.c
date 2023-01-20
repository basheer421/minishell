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

// set return status to 1 in case of error
int	ms_cd(t_ms *shell, char **path, int arg_count)
{
	char	cur_dir[MAXPATHLEN];
	char	*new_dir;
	char	*pwd;

	if (arg_count > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	else
	{
		if (arg_count == 1)
		{
			new_dir = (char *)ht_get(shell->env_vars, "HOME");
			if (!new_dir)
			{
				printf("cd: HOME not set\n");
				return (1);
			}
		}
		else
			new_dir = path[1];
		// runs cd on given path and checks if it was successful
		if (new_dir && ms_errno_check(ft_strjoin("cd: ", new_dir), \
			chdir(new_dir)) == 0)
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
		}
	}
	return (0);
}

/**
 * @test for PWD and OLDPWD
 * when PWD and OLDPWD are unset, do nothing
 * when PWD is unset and we're changing dir, OLDPWD should be set to an empty string
 * when PWD is set but OLDPWD is unset, OLDPWD must be automatically recreated on cd
 */