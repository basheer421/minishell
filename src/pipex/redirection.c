/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 02:53:14 by mfirdous          #+#    #+#             */
/*   Updated: 2023/01/24 02:53:14 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_heredoc(char *delim, int pipe[])
{
	char	*line;
	int		d_len;

	d_len = ft_strlen(delim);
	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, delim, d_len) && !line[d_len + 1])
			break ;
		write(pipe[1], line, ft_strlen(line));
		write(STDOUT_FILENO, "> ", 2);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
}

int	redirect_file(char *file_name, int pipe_end, int open_flags)
{
	int	file;

	file = open(file_name, open_flags, 0777);
	if (file == -1)
	{
		perror(file_name);
		close(file);
		return (0);
	}
	dup2(file, pipe_end);
	close(file);
	return (1);
}

int	redirect_input(t_list *inputs, int p[], bool is_first)
{
	// if (is_first)
	// {
	// 	printf("is first\n");
	// 	dup2(STDIN_FILENO, p[0]);
	// }
	// (void)inputs;
	// (void)p;
	// return (1);

	int		i;
	int		temp_pipe[2];
	t_list	*node;
	t_file	*input_file;

	i = -1;
	node = inputs;
	check_err("pipe", pipe(temp_pipe));
	if (!node->content && is_first)
	{
		printf("is first\n");
		dup2(STDIN_FILENO, p[0]);
	}
	else
		while (node)
		{
			input_file = (t_file *)node->content;
			if (!input_file)
				break ;
			if (input_file->is_extra && !node->next)// is a heredoc
			{
				printf("heredoc to real pipe\n");
				get_heredoc(input_file->name, p);
			}
			else if (input_file->is_extra)
			{
				printf("heredoc to fake pipe\n");
				get_heredoc(input_file->name, temp_pipe);
			}
			else
			{
				// is last node and redirection failed
				if (!node->next && !redirect_file(input_file->name, p[0], O_RDONLY))
					return (close(temp_pipe[0]), close(temp_pipe[1]), 0);
				else if (node->next && !redirect_file(input_file->name, temp_pipe[0], O_RDONLY))
					return (close(temp_pipe[0]), close(temp_pipe[1]), 0);
			}
			node = node->next;
		}
	return (close(temp_pipe[0]), close(temp_pipe[1]), 1);
}

int	redirect_output(t_list *outputs, int p[], bool is_last)
{
	// if (is_last)
	// {
	// 	printf("is last\n");
	// 	dup2(STDOUT_FILENO, p[1]);
	// }
	// (void)outputs;
	// (void)p;
	// return (1);

	int		i;
	int		temp_pipe[2];
	int		open_flags;
	t_list	*node;
	t_file	*output_file;

	i = -1;
	node = outputs;
	check_err("pipe", pipe(temp_pipe));
	if (!node->content && is_last) // no o/p redirects and is the last cmd
	{
		printf("is last\n\n");
		dup2(STDOUT_FILENO, p[1]);
	}
	else
		while (node)
		{
			output_file = (t_file *)node->content;
			if (!output_file)
				break ;
			if (output_file->is_extra)
				open_flags = O_WRONLY | O_APPEND | O_CREAT;
			else
				open_flags = O_WRONLY | O_TRUNC | O_CREAT;
			if (!node->next && !redirect_file(output_file->name, p[1], open_flags))
				return (close(temp_pipe[0]), close(temp_pipe[1]), 0);
			else if (node->next && !redirect_file(output_file->name, temp_pipe[1], open_flags))
					return (close(temp_pipe[0]), close(temp_pipe[1]), 0);
			node = node->next;
		}
	return (close(temp_pipe[0]), close(temp_pipe[1]), 1);
}

// go thru all inputs first
// while (go through all heredocs)
// if you see a heredoc
// 		if its the last input, 
//			read from STDIN into a pipe[1] and use pipe[0] as the final fd
//		if its not the last input,
//			read from STDIN into a temppipe[1] and close both ends
// while (rest of the inputs)
// if is a regular input
//	 	if its the last input,
//			finalfd = open(file)
//		else if its not the last input
//			tempfd = open(file), close tempfd
