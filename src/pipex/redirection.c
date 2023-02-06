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

// if there is no redir, then run the cmd normally with the prev pipe,
// if there is a redir but the file is invalid, then dont run the cmd

static int	open_file(char *file_name, int open_flags)
{
	int	file;

	file = open(file_name, open_flags, 0777);
	if (file == -1)
		perror(file_name);
	return (file);
}

// creates a pipe, writes to it whatever is read from STDIN till delim is input, 
// returns the read end of the pipe and closes the write end
int	get_heredoc(char *delim)
{
	int		p[2];
	char	*line;
	int		d_len;
	int		pid;
	int		status;

	check_err("pipe", pipe(p));
	pid = check_err("fork", fork());
	if (pid == 0)
	{
		d_len = ft_strlen(delim);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			if (!ft_strncmp(line, delim, d_len) && !line[d_len + 1])
				break ;
			write(p[1], line, ft_strlen(line));
			write(STDOUT_FILENO, "> ", 2);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		free(line);
		close(p[1]);
		close(p[0]);
	}
	close(p[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		g_exit_status = ms_get_sig_status(WTERMSIG(status));
	return (p[0]);
}

// chunks[i]->in_redir_fd is set to -2 if there is no input redir, -1 if the given redir was an invalid file
void	redirect_input(t_cmd_chunk **chunks)
{
	int		i;
	t_list	*node;
	t_file	*input_file;

	i = -1;
	while (chunks[++i])
	{
		chunks[i]->in_redir_fd = -1;
		node = chunks[i]->inputs;
		if (node && !node->content) // there are no redirs for this cmd_chunk
		{
			if (i == 0) // if this is the first cmd 
				chunks[i]->in_redir_fd = STDIN_FILENO;
			else
				chunks[i]->in_redir_fd = -2;
		}
		else
		{
			while (node) // check heredocs
			{
				input_file = (t_file *)node->content;
				if (input_file->is_extra && !node->next) // is a heredoc and is the last input
					chunks[i]->in_redir_fd = get_heredoc(input_file->name);
				else if (input_file->is_extra)
					check_err("close", close(get_heredoc(input_file->name)));
				node = node->next;
			}
			node = chunks[i]->inputs;
			while (node) // check input files
			{
				input_file = (t_file *)node->content;
				if (!input_file->is_extra)
				{
					chunks[i]->in_redir_fd = open_file(input_file->name, O_RDONLY);
					if (chunks[i]->in_redir_fd == -1)
						break;
					if (node->next)
						close(chunks[i]->in_redir_fd);
				}
				node = node->next;
			}
		}
	}
}

void redirect_output(t_cmd_chunk **chunks)
{
	int		i;
	int		open_flags;
	t_list	*node;
	t_file	*output_file;

	i = -1;
	while (chunks[++i])
	{
		chunks[i]->out_redir_fd = -1;
		if (chunks[i]->in_redir_fd != -1)
		{
			node = chunks[i]->outputs;
			if (node && !node->content)
			{
				if (!chunks[i + 1]) // is the last command
					chunks[i]->out_redir_fd = STDOUT_FILENO;
				else
					chunks[i]->out_redir_fd = -2; // no output redirs for this cmd_chunk
			}
			else
			{
				while (node)
				{
					output_file = (t_file *)node->content;
					open_flags = O_WRONLY | O_TRUNC | O_CREAT;
					if (output_file->is_extra)
						open_flags = O_WRONLY | O_APPEND | O_CREAT;
					chunks[i]->out_redir_fd = open_file(output_file->name, open_flags);
					if (chunks[i]->out_redir_fd == -1)
						break;
					if (node->next)
						close(chunks[i]->out_redir_fd);
					node = node->next;
				}
			}
		}
	}
}
