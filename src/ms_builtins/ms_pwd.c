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

void	ms_pwd(t_ms *shell)
{
	char *pwd_value = "sfasf";
	pwd_value = ht_get(shell->env_vars, "pwd");
	printf("%s\n", (char *)pwd_value);
}