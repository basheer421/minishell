/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:41:28 by bammar            #+#    #+#             */
/*   Updated: 2022/08/14 16:26:19 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !*lst || !del)
		return ;
	ft_lstiter(*lst, del);
	temp = NULL;
	while (*lst)
	{
		temp = *lst;
		*lst = (*(lst))->next;
		free(temp);
	}
	lst = NULL;
}
