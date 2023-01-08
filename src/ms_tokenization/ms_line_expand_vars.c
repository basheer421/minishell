/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_expand_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:30:45 by bammar            #+#    #+#             */
/*   Updated: 2023/01/09 00:39:37 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_expand_vars
{
	char	*var_name;
	bool	inside_quotes;
	bool	inside_dquotes;
}		t_expand_vars;


static int	first_nonalnum(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isalnum(s[i]))
		i++;
	if (!s[i])
		return (-1);
	return (s[i]);
}

static char	*get_next_var(char *string, int i)
{
	int			sub_len;
	char		*var_name;

	sub_len = ft_index(string + i + 1, first_nonalnum(string));
	if (sub_len == -1)
		sub_len = ft_strlen(string);
	var_name = ft_substr(string, i + 1, sub_len);
	if (!var_name)
		return (NULL);
	string += i + 1 + sub_len;
	return (var_name);
}

static t_list	**read_string(char *string, t_expand_vars *vars)
{
	int			i;
	t_list		*lst[2];

	
	lst[0] = ft_lstnew(NULL);
	if (lst[0])
		return (NULL);
	lst[1] = ft_lstnew(NULL);
	if (lst[1])
		return (NULL);
	i = -1;
	while (string[++i])
	{
		if (string[i] == '\'' && !vars->inside_dquotes)
			vars->inside_quotes = !vars->inside_quotes;
		else if (string[i] == '\"' && !vars->inside_quotes)
			vars->inside_dquotes = !vars->inside_dquotes;
		else if (string[i] == '$' && ft_strlen(string) == 1
			&& (vars->inside_dquotes && !vars->inside_quotes))
		{
			ft_lstadd_back(&lst[1], ft_lstnew(get_next_var(string, i)));
		}
		else
		{
			ft_lstadd_back(&lst[0], &string[i]);
		}
	}
	return (lst);
}

// static char	*chunk_expand(char *chunk)
// {
// 	int				word_count;
// 	t_list			*lst;
// 	t_expand_vars	vars;
// 	char			**words;


// 	words = split_with_no_quotes(chunk, ' ');
// 	if (!words)
// 		return (NULL);
// 	lst = ft_lstnew(NULL);
// 	if (!lst)
// 		return (ft_split_destroy(words), NULL);
// 	word_count = -1;
// 	while (words[++word_count])
// 	{
// 		;
// 	}
// 	ft_split_destroy(words);	
// }

// "'$PATH'"

// bool	ms_line_expand_vars(char **string_chunks)
// {
// 	int		i;
// 	char	*temp;

// 	i - 1;
// 	while (string_chunks[++i])
// 	{
// 		temp = string_chunks[i];
// 		string_chunks[i] = chunk_expand(string_chunks[i]);
// 		free(temp);
// 		if (!string_chunks[i])
// 			return (false);
// 	}
// 	return (true);
// }
