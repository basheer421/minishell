/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:16:37 by bammar            #+#    #+#             */
/*   Updated: 2022/12/24 17:05:47 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht.h"

void	ht_clear(t_ht *table)
{
	char	*reached_key;
	int		i;

	if (ht_isempty(table))
		return ;
	i = 0;
	while (table->array[i] && table->size > 0)
	{
		reached_key = table->array[i]->key;
		while (reached_key != NULL)
		{
			ht_remove(table, reached_key);
			reached_key = table->array[i]->key;
		}
		i++;
	}
}
