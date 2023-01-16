/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 01:43:40 by bammar            #+#    #+#             */
/*   Updated: 2023/01/16 10:31:22 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht.h"

void	ht_replace(t_ht *table, char *key, void *new_value)
{
	if (!ht_contains(table, key))
		return ;
	ht_remove(table, key);
	ht_set(table, key, new_value);
}
