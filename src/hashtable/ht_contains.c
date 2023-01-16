/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_contains.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:16:51 by bammar            #+#    #+#             */
/*   Updated: 2023/01/16 10:13:52 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht.h"

int	ht_contains(t_ht *table, const char *key)
{
	int	found;

	found = 0;
	ht_get(table, key, &found);
	return (found);
}
