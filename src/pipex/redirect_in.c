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

static void	run_heredoc(int p[], char *delim)
{
	char	*line;
	int		d_len;

	d_len = ft_strlen(delim);
	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (g_exit_status == 130 || \
			(!ft_strncmp(line, delim, d_len) && !line[d_len + 1]))
			break ;
		write(p[1], line, ft_strlen(line));
		write(STDOUT_FILENO, "> ", 2);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(p[1]);
	close(p[0]);
	exit(g_exit_status);
}

// creates a pipe, writes to it whatever is read from STDIN till delim is input, 
// returns the read end of the pipe and closes the write end
static int	get_heredoc_pipe(char *delim)
{
	int		p[2];
	int		pid;
	int		status;

	check_err("pipe", pipe(p));
	pid = check_err("fork", fork());
	if (pid == 0)
		run_heredoc(p, delim);
	close(p[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		g_exit_status = ms_get_sig_status(WTERMSIG(status));
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (p[0]);
}

static void	check_heredocs(t_cmd_chunk *cmd)
{
	t_list	*node;
	t_file	*input_file;

	node = cmd->inputs;
	while (node && g_exit_status != 130)
	{
		input_file = (t_file *)node->content;
		if (input_file)
		{
			if (input_file->is_extra && !node->next) // is a heredoc and is the last input
				cmd->in_redir_fd = get_heredoc_pipe(input_file->name);
			else if (input_file->is_extra)
				close(get_heredoc_pipe(input_file->name));
		}
		node = node->next;
	}
}

static void		check_input_files(t_cmd_chunk *cmd)
{
	t_list	*node;
	t_file	*input_file;
	int		infile_fd;

	node = cmd->inputs;
	while (node && g_exit_status != 130) // check input files
	{
		input_file = (t_file *)node->content;
		if (input_file && !input_file->is_extra)
		{
			infile_fd = open_file(input_file->name, O_RDONLY);
			if (infile_fd == -1)
			{
				g_exit_status = 1;
				break;
			}	
			if (!node->next)
				cmd->in_redir_fd = infile_fd;
			else
				close(infile_fd);
		}
		node = node->next;
	}
}

// chunks[i]->in_redir_fd is set to -2 if there is no input redir, -1 if the given redir was an invalid file
void	redirect_input(t_cmd_chunk **cmds)
{
	int		i;

	i = -1;
	g_exit_status = 0;
	if (cmds[0]->inputs && !(cmds[0]->inputs->content))
		cmds[++i]->in_redir_fd = STDIN_FILENO;
	while (cmds[++i])
	{
		cmds[i]->in_redir_fd = -1;
		if (cmds[i]->inputs && !(cmds[i]->inputs->content)) // there are no redirs for this cmd_chunk
			cmds[i]->in_redir_fd = -2;
		else
			check_heredocs(cmds[i]);
	}	
	i = -1;
	while (cmds[++i])
		check_input_files(cmds[i]);
}
