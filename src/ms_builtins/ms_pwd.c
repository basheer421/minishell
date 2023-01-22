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

int	ms_pwd(void)
{
	char	cur_dir[MAXPATHLEN];

	if (!getcwd(cur_dir, MAXPATHLEN))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cur_dir);
	return (EXIT_SUCCESS);
}