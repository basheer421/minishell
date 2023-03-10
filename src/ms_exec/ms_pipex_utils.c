/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:17:27 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/23 20:17:27 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *file_name, int open_flags)
{
	int	file;

	file = open(file_name, open_flags, 0644);
	if (file == -1)
		perror(file_name);
	return (file);
}

int	is_regular_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

static void	free_strs(char **args, char *str, int index)
{
	if (args)
	{
		while (args[index])
			free(args[index++]);
		free(args);
	}
	if (str)
		free(str);
}

// Returns a list of each colon-separated directory name as an array of strings
static char	**parse_path(char **envp)
{
	char	path_var[5];
	int		i;

	i = -1;
	while (envp[++i])
	{
		ft_strlcpy(path_var, envp[i], 5);
		if (ft_strncmp(path_var, "PATH", 4) == 0)
			return (ft_split(envp[i] + 5, ':'));
	}
	return (0);
}

// Returns the command file path if found in PATH, NULL if file does not exist
char	*get_pathname(char *cmd_name, char **envp)
{
	char	*path_name;
	char	*file_name;
	char	**paths;
	int		i;

	paths = parse_path(envp);
	if (!paths || !paths[0])
	{
		ft_split_destroy(paths);
		return (NULL);
	}
	file_name = ft_strjoin("/", cmd_name);
	i = -1;
	while (paths[++i])
	{
		path_name = ft_strjoin(paths[i], file_name);
		if (access(path_name, F_OK) == 0 && is_regular_file(path_name))
			break ;
		free(path_name);
		free(paths[i]);
		path_name = 0;
	}
	free_strs(paths, file_name, i);
	return (path_name);
}
