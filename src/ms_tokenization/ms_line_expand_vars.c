/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_expand_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:30:45 by bammar            #+#    #+#             */
/*   Updated: 2023/01/09 15:25:04 by bammar           ###   ########.fr       */
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
	t_list		*lsts[2];

	lsts[0] = ft_lstnew(NULL);
	if (!lsts[0])
		return (NULL);
	lsts[1] = ft_lstnew(NULL);
	if (!lsts[1])
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
			ft_lstadd_back(&lsts[0], ft_strdup("\0"));
			ft_lstadd_back(&lsts[1], ft_lstnew(get_next_var(string, i)));
		}
		else
			ft_lstadd_back(&lsts[0], &string[i]);
	}
	return (lsts);
}

static int	expandlsts_size(t_list **lsts)
{
	t_list	*nodes[2];
	int		size;

	nodes[0] = lsts[0];
	nodes[1] = lsts[1];
	size = 0;
	while (nodes[0])
	{
		if (*((char *)(nodes[0]->content)))
			size++;
		else if (nodes[1])
		{
			size += ft_strlen(nodes[1]->content);
			nodes[1] = nodes[1]->next;
		}
		nodes[0] = nodes[0]->next;
	}
	return (size);
}

static char	*join_expandlsts(t_list **lsts)
{
	t_list	*nodes[2];
	int		size;
	int		i;
	char	*new_string;

	nodes[0] = lsts[0]->next;
	nodes[1] = lsts[1]->next;
	size = expandlsts_size(nodes);
	new_string = malloc(size + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	while (nodes[0])
	{
		if (*((char *)(nodes[0]->content)))
			new_string[i++] = *((char *)(nodes[0]->content));
		else if (nodes[1])
		{
			ft_memcpy(new_string + i, 
				nodes[1]->content, ft_strlen(nodes[1]->content));
			i += ft_strlen(nodes[1]->content);
			nodes[1] = nodes[1]->next;
		}
		nodes[0] = nodes[0]->next;
	}
	return (new_string);
}

// using read_string, it goes through each word in that string
// 	and adds each letter to "lst 0" and if a variable is found
//	it stores the name of the variable in "lst 1" 
//	and puts a '\0' as a place holder,
//	so whenever '\0' is found we call the last variable inside "lst 1"
//	and we join everything togather replacing all '\0's with their values
static char	*chunk_expand(char *chunk)
{
	int				word_count;
	t_list			**lsts;
	t_expand_vars	vars;
	char			**words;
	char			*new_chunk;
	char			*temp;


	words = split_with_no_quotes(chunk, ' ');
	if (!words)
		return (NULL);
	word_count = -1;
	while (words[++word_count])
	{
		ft_bzero(&vars, sizeof(t_expand_vars));
		lsts = read_string(words, &vars);
		if (!lsts)
			return (NULL);
		words[word_count] = join_expandlsts(lsts);
		if (!words[word_count])
			return (NULL);
	}
	word_count = -1;
	new_chunk = ft_strdup("\0");
	if (!new_chunk)
		return (NULL);
	while (words[++word_count])
	{
		temp = new_chunk;
		ft_strjoin(new_chunk, words[word_count]);
		free(temp);
		if (!new_chunk)
			return (NULL);
	}
	ft_split_destroy(words);
	return (new_chunk);
}

bool	ms_line_expand_vars(char **string_chunks)
{
	int		i;
	char	*temp;

	i - 1;
	while (string_chunks[++i])
	{
		temp = string_chunks[i];
		string_chunks[i] = chunk_expand(string_chunks[i]);
		free(temp);
		if (!string_chunks[i])
			return (false);
	}
	return (true);
}
