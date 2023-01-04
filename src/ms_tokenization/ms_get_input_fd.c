/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_input_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 21:46:05 by bammar            #+#    #+#             */
/*   Updated: 2023/01/04 22:14:33 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_get_input_fd(char *file_name)
{
	if (!file_name || access(file_name, F_OK) != 0)
		return (-1);
	return (open(file_name, O_RDONLY));
}
