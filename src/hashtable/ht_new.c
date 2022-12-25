/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 00:13:56 by bammar            #+#    #+#             */
/*   Updated: 2022/12/24 14:25:17 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht.h"

t_ht	*ht_new(size_t size)
{
	t_ht	*table;
	size_t	i;

	table = malloc(sizeof(t_ht));
	if (!table)
		return (NULL);
	table->total_size = size;
	table->array = malloc((size + 1) * sizeof(t_node *));
	if (!table->array)
		return (free(table), NULL);
	i = 0;
	while (i < size)
	{
		table->array[i] = malloc(sizeof(t_node));
		if (table->array[i] == NULL)
			return (NULL);
		table->array[i]->key = NULL;
		table->array[i]->value = NULL;
		table->array[i++]->next = NULL;
	}
	table->array[i] = NULL;
	table->size = 0;
	return (table);
}
