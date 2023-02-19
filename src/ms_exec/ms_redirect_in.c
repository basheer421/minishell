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

static void	run_heredoc(int p[], char *delim, t_ms *shell)
{
	char	*line;
	int		d_len;

	signal(SIGINT, ms_hdoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
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
	ms_destroy(shell);
	exit(g_exit_status);
}

// creates a pipe, writes to it whatever is read from STDIN till delim is input, 
// returns the read end of the pipe and closes the write end
static int	get_heredoc_pipe(char *delim, t_ms *shell)
{
	int		p[2];
	int		pid;
	int		status;

	check_err("pipe", pipe(p));
	pid = check_err("fork", fork());
	if (pid == 0)
		run_heredoc(p, delim, shell);
	close(p[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		g_exit_status = ms_get_sig_status(WTERMSIG(status));
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (p[0]);
}

static void	check_heredocs(t_ms *shell, int i)
{
	t_list	*node;
	t_file	*input_file;
	t_cmd_chunk *cmd;

	cmd = shell->cur_cmd[i];
	node = cmd->inputs;
	while (node && g_exit_status != 130)
	{
		input_file = (t_file *)node->content;
		if (input_file)
		{
			if (input_file->is_extra && !node->next) // is a heredoc and is the last input
				cmd->in_redir_fd = get_heredoc_pipe(input_file->name, shell);
			else if (input_file->is_extra)
				close(get_heredoc_pipe(input_file->name, shell));
		}
		node = node->next;
	}
}

static	void	check_input_files(t_cmd_chunk *cmd)
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
				break ;
			}
			if (!node->next)
				cmd->in_redir_fd = infile_fd;
			else
				close(infile_fd);
		}
		node = node->next;
	}
}

int	save_exit_status(t_cmd_chunk *chunk, int old_exit_status)
{
	if (chunk && chunk->cmd)
		if ((ft_strncmp(chunk->cmd[0], "exit", 5) == 0) && !chunk->cmd[1])
		{
			ft_split_destroy(chunk->cmd);
			chunk->cmd = ft_malloc(sizeof(char *) * 3);
			chunk->cmd[0] = ft_strdup("exit");
			chunk->cmd[1] = ft_itoa(old_exit_status);
			chunk->cmd[2] = NULL;
		}
	return (1);
}

/*static  void    show_chunks(t_cmd_chunk **chunks)
{
	int		i;
	int		j;
	t_file	*file;
	t_list	*node;

	i = -1;
	printf("\n");

	while (chunks[++i])
	{
		printf("chunk %d\n", i);
		j = -1;
		if (chunks[i]->cmd)
			while (chunks[i]->cmd[++j] != NULL)
				printf("cmds:%s\n", chunks[i]->cmd[j]);
		node = (t_list *)chunks[i]->inputs;
		printf("input redirects: \n");
		while (node)
		{
			file = (t_file *)node->content;
			if (file)
				printf("%s %d\n", file->name, file->is_extra);
			else
				printf("end\n");
			node = node->next;
		}
		node = (t_list *)chunks[i]->outputs;
		printf("output redirects: \n");
		while (node)
		{
			file = (t_file *)node->content;
			if (file)
				printf("%s %d\n", file->name, file->is_extra);
			else
				printf("end\n");
			node = node->next;
		}
	}
	printf("--------------\n\n");
}*/

// chunks[i]->in_redir_fd is set to -3 if its the first cmd and there's no redir, 
// 									-2 if its a non-first cmd and there is no input redir, 
//									-1 if the given redir was an invalid file
void	redirect_input(t_ms *shell)
{
	int	i;
	int	old_exit_status;
	t_cmd_chunk **cmds;

	cmds = shell->cur_cmd;
	// show_chunks(cmds);
	old_exit_status = g_exit_status;
	g_exit_status = 0;
	i = -1;
	if (cmds[0]->inputs && !(cmds[0]->inputs->content) \
		&& save_exit_status(cmds[0], old_exit_status))
		cmds[++i]->in_redir_fd = STDIN_FILENO;
	while (cmds[++i] && save_exit_status(cmds[i], old_exit_status))
	{
		cmds[i]->in_redir_fd = -1;
		if (cmds[i]->inputs && !(cmds[i]->inputs->content)) // if there are no redirs for this cmd_chunk
			cmds[i]->in_redir_fd = -2;
		else
			check_heredocs(shell, i);
	}
	i = -1;
	while (cmds[++i] && save_exit_status(cmds[i], old_exit_status))
		check_input_files(cmds[i]);
}
