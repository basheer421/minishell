/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_contains.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:16:51 by bammar            #+#    #+#             */
/*   Updated: 2023/01/18 17:35:51 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht.h"

int	ht_contains(t_ht *table, const char *key)
{
	unsigned int	index;
	size_t			string_length;
	t_node			*node;
	char			*key_value;

	if (!key || ht_isempty(table))
		return (0);
	key_value = ft_strdup(key);
	if (!key_value)
		return (0);
	index = ht_hash(table, ft_strdup(key));
	node = table->array[index];
	while (node && node->key)
	{
		string_length = ft_strlen(node->key);
		if (string_length < ft_strlen(key_value))
			string_length = ft_strlen(key_value);
		if (ft_strncmp(node->key, key_value, string_length) == 0)
			return (free(key_value), 1);
		node = node->next;
	}
	return (free(key_value), 0);
}
