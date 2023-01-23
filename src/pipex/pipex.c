/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:57:10 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/23 18:57:10 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_cmd(int p1[], int p2[], char **cmd, t_ms *shell)
{
	int			pid;
	t_alloced	*c;

	pid = check_err("fork", fork());
	if (pid == 0)
	{	
		close(p2[0]);
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		dup2(p2[1], STDOUT_FILENO);
		close(p2[1]);
		if (handle_builtins(cmd, shell))
			exit(g_exit_status);
		c = check_cmd_path(p1, p2, cmd, shell);
		check_err("execve", execve(c->path, cmd, c->envp));
	}
	close(p1[0]);
	close(p2[1]);
	return (pid);
}

int	check_heredoc(char **argv, int pipe[], int *i)
{
	char	*line;
	int		d_len;

	if (ft_strncmp("here_doc", argv[1], 9) == 0)
	{
		d_len = ft_strlen(argv[2]);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			if (!ft_strncmp(line, argv[2], d_len) && !line[d_len + 1])
				break ;
			write(pipe[1], line, ft_strlen(line));
			write(STDOUT_FILENO, "> ", 2);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		*i = 2;
		free(line);
		return (O_WRONLY | O_APPEND | O_CREAT);
	}
	*i = 1;
	redirect_file(argv[1], pipe[0], O_RDONLY);
	return (O_WRONLY | O_TRUNC | O_CREAT);
}

int	wait_cmds(int *pids, int count)
{
	int	i;
	int	status;

	i = -1;
	while (++i < count)
		waitpid(pids[i], &status, 0);
	free(pids);
	// if (WIFSIGNALED(status))
	// 	return (WTERMSIG(status));
		return (WEXITSTATUS(status));
	return (1);
}

// for now uses stdin for first command and stdout for last command
int	pipex(t_cmd_chunk **chunks, int cmd_count, t_ms *shell)
{	
	int		pipes[2][2];
	int		*pids;
	int		i;
	int		pipe_no;

	check_err("pipe", pipe(pipes[0]));
	close(pipes[0][1]);
	pids = (int *)malloc(sizeof(int) * (cmd_count));
	pipe_no = 0;
	i = -1;
	dup2(STDIN_FILENO, pipes[0][0]);					// will remove later
	while (chunks[++i])
	{
		// redirect input
		// redirect output
		check_err("pipe", pipe(pipes[!pipe_no]));
		if (!chunks[i + 1])								// will remove later
			dup2(STDOUT_FILENO, pipes[!pipe_no][1]); 	// because chunks->input and chunks->output will be used instead
		pids[i] = exec_cmd(pipes[pipe_no], pipes[!pipe_no], chunks[i]->cmd, shell);
		pipe_no = !pipe_no;
	}
	close(pipes[pipe_no][0]);
	return (wait_cmds(pids, i));
}
