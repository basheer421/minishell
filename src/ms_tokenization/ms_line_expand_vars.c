/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_expand_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:30:45 by bammar            #+#    #+#             */
/*   Updated: 2023/01/18 16:37:29 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void printlst(t_list *lst)
// {
// 	t_list *node = lst;

// 	while (node)
// 	{
// 		puts(node->content);
// 		node = node->next;
// 	}
// }

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

static char	*get_next_var(char *string, int *index)
{
	int			sub_len;
	char		*var_name;
	int			i;

	i = *index;
	sub_len = ft_index(string + i + 1, first_nonalnum(string));
	if (sub_len == -1)
		sub_len = ft_strlen(string);
	var_name = ft_substr(string, i + 1, sub_len);
	if (!var_name)
		return (NULL);
	*index += 1 + sub_len;
	return (var_name);
}

static t_list	**read_string(char *string, t_expand_vars *vars)
{
	int			i;
	t_list		**lsts;

	lsts = malloc(2 * sizeof(t_list *));
	if (!lsts)
		return (NULL);
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
			ft_lstadd_back(&lsts[0], ft_lstnew(ft_strdup("\0")));
			ft_lstadd_back(&lsts[1], ft_lstnew(get_next_var(string, &i)));
		}
		else
			ft_lstadd_back(&lsts[0], ft_lstnew(&string[i]));
	}
	// printlst(lsts[0]->next);
	return (lsts);
}

static int	expandlsts_size(t_list **lsts, t_ms *shell)
{
	t_list	*nodes[2];
	int		size;
	char	*var_value;

	nodes[0] = lsts[0];
	nodes[1] = lsts[1];
	size = 0;
	while (nodes[0])
	{
		if (*((char *)(nodes[0]->content)))
			size++;
		else if (nodes[1])
		{
			var_value = ht_get(shell->env_vars, nodes[1]->content);
			if (var_value)
				size += ft_strlen(var_value);
			nodes[1] = nodes[1]->next;
		}
		nodes[0] = nodes[0]->next;
	}
	return (size);
}

static char	*join_expandlsts(t_list **lsts, t_ms *shell)
{
	t_list	*nodes[2];
	int		size;
	int		i;
	char	*new_string;
	char	*var_value;

	nodes[0] = lsts[0]->next;
	nodes[1] = lsts[1]->next;
	size = expandlsts_size(nodes, shell);
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
			var_value = ht_get(shell->env_vars, nodes[1]->content);
			if (!var_value)
				var_value = ft_strdup("\0");
			ft_memcpy(new_string + i, var_value,
				ft_strlen(var_value));
			i += ft_strlen(var_value);
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
static char	*chunk_expand(char *chunk, t_ms *shell)
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
		lsts = read_string(words[word_count], &vars);
		if (!lsts)
			return (NULL);
		words[word_count] = join_expandlsts(lsts, shell);
		if (!words[word_count])
			return (NULL);
	}
	word_count = -1;
	new_chunk = ft_strdup(words[++word_count]);
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

bool	ms_line_expand_vars(char **string_chunks, t_ms *shell)
{
	int		i;
	char	*temp;

	i = -1;
	while (string_chunks[++i])
	{
		temp = string_chunks[i];
		string_chunks[i] = chunk_expand(string_chunks[i], shell);
		free(temp);
		if (!string_chunks[i])
			return (false);
	}
	return (true);
}
