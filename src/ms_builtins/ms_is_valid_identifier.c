/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_valid_identifier.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:19:16 by mfirdous          #+#    #+#             */
/*   Updated: 2023/02/25 15:50:29 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_is_valid_identifier(char *str, char *func)
{
	int		i;
	bool	is_valid;

	i = 0;
	is_valid = true;
	if (!str[0] || !ft_isalpha(str[0]))
		is_valid = false;
	else if (str[0])
	{
		printf("str %s \n", str);
		while (str[++i])
			if (!ft_isalnum(str[i]))
				is_valid = false;
	}
	if (!is_valid)
	{
		printf("%s: \'%s\': not a valid identifier\n", func, str);
		return (false);
	}
	return (true);
}
