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

#include "pipex.h"

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

int	exec_cmd(int p1[], int p2[], char *cmd_str, char **envp)
{
	int			pid;
	t_alloced	*c;

	pid = check_err("fork", fork());
	if (pid == 0)
	{	
		close(p2[0]);
		c = check_cmd(p1, p2, cmd_str, envp);
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		dup2(p2[1], STDOUT_FILENO);
		close(p2[1]);
		check_err("execve", execve(c->path, c->cmd, envp));
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
		waitpid(pids[0], &status, 0);
	free(pids);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	main(int argc, char**argv, char**envp)
{	
	int	pipes[2][2];
	int	open_flags;
	int	*pids;
	int	count;
	int	i;

	if (argc < 4)
		exit_msg("pipex", WRONG_ARG_COUNT, 2, NULL);
	check_err("pipe", pipe(pipes[0]));
	open_flags = check_heredoc(argv, pipes[0], &i);
	close(pipes[0][1]);
	pids = (int *)malloc(sizeof(int) * (argc - i - 2));
	argv += i;
	i = 0;
	count = 0;
	while (*(++argv + 1))
	{
		check_err("pipe", pipe(pipes[!i]));
		if (!argv[2])
			redirect_file(argv[1], pipes[!i][1], open_flags);
		pids[count++] = exec_cmd(pipes[i], pipes[!i], *argv, envp);
		i = !i;
	}
	close(pipes[i][0]);
	return (wait_cmds(pids, count));
}
