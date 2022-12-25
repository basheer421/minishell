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

int	redirect_file(char *file_name, int pipe_end, int write)
{
	int	file;

	if (!write)
		file = open(file_name, O_RDONLY, 0777);
	else
		file = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
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
	return (pid);
}

int	main(int argc, char**argv, char**envp)
{
	int	p[2][2];
	int	status;
	int	i;
	int	pid[2];

	if (argc != 5)
		exit_msg("pipex", WRONG_ARG_COUNT, 2, NULL);
	i = -1;
	check_err("pipe", pipe(p[0]));
	while (++i < 2)
	{
		check_err("pipe", pipe(p[!i]));
		close(p[0][!i]);
		if (redirect_file(argv[i * 3 + 1], p[0][i], i))
			pid[i] = exec_cmd(p[i], p[!i], argv[i + 2], envp);
		close(p[i][0]);
		close(p[!i][1]);
	}
	i = -1;
	while (++i < 2)
		waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
