/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:39:03 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/10 16:39:03 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtins(char *line, t_ms *shell)
{
	char	**strs;
	int		arg_count;
	
	strs = ft_split2(line, " ", &arg_count);
	if (strs && strs[0])
	{
		if (ft_strncmp(strs[0], "echo", 5) == 0)
		{
			if (strs[1] && ft_strncmp(strs[1], "-n", 3) == 0) // -n flag is set to true
				ms_echo(strs, 1);
			else
				ms_echo(strs, 0);
		}
		else if (ft_strncmp(strs[0], "pwd", 4) == 0)
			ms_pwd();
		else if (ft_strncmp(strs[0], "exit", 5) == 0)
			ms_exit(strs, arg_count, line, shell);
		else if (ft_strncmp(strs[0], "cd", 3) == 0)
			ms_cd(shell, strs, arg_count);
		else if (ft_strncmp(strs[0], "env", 4) == 0)
			ms_env(shell);
		else if (ft_strncmp(strs[0], "export", 7) == 0)
			ms_export(shell, strs, arg_count);
		else if (ft_strncmp(strs[0], "unset", 6) == 0)
			ms_unset(shell, strs, arg_count);
		ft_split_destroy(strs);
	}
}
