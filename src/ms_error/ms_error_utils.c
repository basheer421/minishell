/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errno_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:39:46 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/08 12:39:46 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Displays error message and exits process if ret_value is -1
 * 
 * @param func_name Name of function to use as header for error message
 * @param ret_value Return value of function being called
 * @return int ret_value
 */
int	check_err(char *func_name, int ret_value)
{
	if (ret_value == -1)
	{
		perror(func_name);
		exit(EXIT_FAILURE);
	}
	return (ret_value);
}

/**
 * @brief Displays error message from perror
 * 
 * @param err_header Name of function to use as header for error message (will be freed)
 * @param ret_value Return value of function being called
 * @return int ret_value
 */
int	ms_errno_check(char *err_header, int ret_value)
{
	if (ret_value == -1)
		perror(err_header);
	if (err_header)
		free(err_header);
	return (ret_value);
}

/**
 * @brief Get the exit status for given errno value
 * 
 * @param err errno value
 * @return int exit status for the process 
 */
int	get_exit_status(int err)
{
	if (err == 2)
		return (127);
	return (126);
}

/**
 * @brief Displays error message to STD_ERR, frees mem and exits the process with err_code
 * 
 * @param heading Heading for error message 
 * @param err_msg Error message 
 * @param err_code Exit status for error message
 * @param mem Memory to be freed before exiting
 */
void	exit_msg(char *heading, char *err_msg, int err_code, t_alloced *mem)
{
	int	i;

	i = -1;
	if (heading && err_msg)
	{
		write(STDERR_FILENO, heading, ft_strlen(heading));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
		write(STDERR_FILENO, "\n", 1);
	}
	if (mem)
	{
		while (++i < 2)
		{
			if (mem->pipes[i][i])
				close(mem->pipes[i][i]);
			if (mem->pipes[i][!i])
				close(mem->pipes[i][!i]);
		}
		free(mem->path);
		ft_split_destroy(mem->envp);
		free(mem);
	}
	exit(err_code);
}
