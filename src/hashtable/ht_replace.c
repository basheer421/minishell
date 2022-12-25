/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 01:43:40 by bammar            #+#    #+#             */
/*   Updated: 2022/12/24 01:54:35 by bammar           ###   ########.fr       */
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
