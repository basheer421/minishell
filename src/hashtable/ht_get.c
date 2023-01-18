/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 00:52:51 by bammar            #+#    #+#             */
/*   Updated: 2023/01/18 15:21:28 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht.h"

void	*ht_get(t_ht *table, const char *key)
{
	unsigned int	index;
	size_t			string_length;
	t_node			*node;
	char			*key_value;

	if (!key || ht_isempty(table))
		return (NULL);
	key_value = ft_strdup(key);
	if (!key_value)
		return (NULL);
	index = ht_hash(table, ft_strdup(key));
	node = table->array[index];
	while (node && node->key)
	{
		string_length = ft_strlen(node->key);
		if (string_length < ft_strlen(key_value))
			string_length = ft_strlen(key_value);
		if (ft_strncmp(node->key, key_value, string_length) == 0)
			return (free(key_value), node->value);
		node = node->next;
	}
	return (free(key_value), NULL);
}
