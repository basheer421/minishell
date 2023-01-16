/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 00:28:18 by bammar            #+#    #+#             */
/*   Updated: 2023/01/16 18:36:23 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht.h"

static int	set_key_and_value(t_ht *table, char *key,
			char *value, t_node *node)
{
	node->key = ft_strdup(key);
	if (!node->key)
		return (0);
	node->value = NULL;
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (0);
	}
	table->size++;
	node->next = NULL;
	return (1);
}

int	ht_set(t_ht *table, char *key, void *value)
{
	unsigned int	index;
	t_node			*node;

	if (ht_contains(table, key))
		return (0);
	index = ht_hash(table, ft_strdup(key));
	node = table->array[index];
	if (node->key == NULL)
		return (set_key_and_value(table, key, value, node));
	while (node->next)
		node = node->next;
	node->next = malloc(sizeof(t_node));
	if (!node->next)
		return (0);
	node = node->next;
	return (set_key_and_value(table, key, value, node));
}
