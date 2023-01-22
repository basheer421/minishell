/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:18:29 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/07 21:18:29 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks if the exit status provided is a string 
static	int	is_invalid_exit_status(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (1); // arg is non numeric, exit with err code 2
	return (0);
}

// confirm if exit status shows as 1 for too many args
int	ms_exit(char **args, int arg_count, t_ms *shell)
{
	int	exit_status;

	printf("exit\n");
	exit_status = 0;
	if (args[1])
	{
		if (is_invalid_exit_status(args[1]))
		{
			printf("exit: numeric argument required\n");
			exit(2);
		}
		exit_status = ft_atoi(args[1]);
	}	
	if (arg_count > 2)
	{
		printf("exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	ft_split_destroy(args);
	ms_destroy(shell);
	exit(exit_status);
}
