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

// cd errors:	too many args
//				no such file or directory
//				permission denied?

// set return status to 1 in case of error
void	ms_cd(t_ms *shell, char **path, int arg_count)
{
	char	*cur_dir;
	char	*new_dir;
	char	*pwd;
	int		found;

	if (arg_count > 2)
		printf("cd: too many arguments\n");
	// check dir permissions
	else
	{
		if (arg_count == 1)
		{
			new_dir = (char *)ht_get(shell->env_vars, "HOME", &found);
			if (!new_dir)
				printf("cd: HOME not set\n");
		}
		else
			new_dir = path[1];
		cur_dir = (char *)malloc(sizeof(char) * MAXPATHLEN);
		// runs cd on given path and checks if it was successful
		found = 0;
		if (new_dir && ms_errno_check(ft_strjoin("cd: ", new_dir), \
			chdir(new_dir)) == 0)
		{
			pwd = (char *)ht_get(shell->env_vars, "PWD", &found);
			if (pwd)
			{
				if (ht_contains(shell->env_vars, "OLDPWD"))
					ht_replace(shell->env_vars, "OLDPWD", pwd);
				else
					ht_set(shell->env_vars, "OLDPWD", pwd);
			}
			else
				ht_replace(shell->env_vars, "OLDPWD", "");
			ht_replace(shell->env_vars, "PWD", getcwd(cur_dir, 256));
		}
		free(cur_dir);
	}
}

/**
 * @test for PWD and OLDPWD
 * when PWD and OLDPWD are unset, do nothing
 * when PWD is unset and we're changing dir, OLDPWD should be set to an empty string
 * when PWD is set but OLDPWD is unset, OLDPWD must be automatically recreated on cd
 */