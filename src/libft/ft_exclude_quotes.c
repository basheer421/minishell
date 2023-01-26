/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exclude_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:54:57 by bammar            #+#    #+#             */
/*   Updated: 2023/01/26 22:26:38 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_inside
{
	int		quotes;
	int		dquotes;
}			t_inside;

static int	count_without_quotes(char *s)
{
	int			i;
	int			count;
	t_inside	inside;

	count = 0;
	i = -1;
	ft_bzero(&inside, sizeof(inside));
	while (s[++i])
	{
		if (s[i] == '\'' && !inside.dquotes)
			inside.quotes = !inside.quotes;
		else if (s[i] == '\"' && !inside.quotes)
			inside.dquotes = !inside.dquotes;
		else
			count++;
	}
	return (count);
}

char	*ft_exclude_quotes(char *str)
{
	int			i;
	int			reach;
	char		*nstr;
	t_inside	inside;

	i = -1;
	reach = 0;
	ft_bzero(&inside, sizeof(inside));
	nstr = ft_malloc(count_without_quotes(str) + 1);
	while (str[++i])
	{
		if (str[i] == '\'' && !inside.dquotes)
			inside.quotes = !inside.quotes;
		else if (str[i] == '\"' && !inside.quotes)
			inside.dquotes = !inside.dquotes;
		else
			nstr[reach++] = str[i];
	}
	nstr[reach] = 0;
	return (nstr);
}
