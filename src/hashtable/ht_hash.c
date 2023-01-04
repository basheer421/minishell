/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 00:25:12 by bammar            #+#    #+#             */
/*   Updated: 2023/01/04 18:16:33 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht.h"

unsigned int	ht_hash(t_ht *table, char *key)
{
	unsigned int	hash;

	hash = table->size;
	free((void *)key);
	return (hash % (table->total_size));
}
