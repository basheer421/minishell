/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_sig_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 00:02:20 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/24 00:02:20 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_get_sig_status(int sig_no)
{
	if (sig_no == SIGINT)
		;
	else if (sig_no == SIGQUIT)
		printf("Quit\n");
	else if (sig_no == SIGSEGV) // remove i guess
		printf("Segmentation faultt\n");
	return (128 + sig_no);
}
