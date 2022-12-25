/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:21:49 by bammar            #+#    #+#             */
/*   Updated: 2022/12/24 15:26:37 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht.h"

void	ht_destroy(t_ht *table)
{
	int	i;

	if (!table)
		return ;
	ht_clear(table);
	i = -1;
	while (table->array[++i])
	{
		free(table->array[i]->key);
		free(table->array[i]->value);
		free(table->array[i]);
	}
	free(table->array);
	free(table);
}
