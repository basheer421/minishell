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

int	ms_errno_check(char *err_header, int ret_value)
{
	if (ret_value == -1)
		perror(err_header);
	if (err_header)
		free(err_header);
	return (ret_value);
}
