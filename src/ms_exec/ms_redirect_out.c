/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 02:40:42 by mfirdous          #+#    #+#             */
/*   Updated: 2023/02/09 02:40:42 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_op_files(t_cmd_chunk *cmd)
{
	t_list	*node;
	t_file	*output_file;
	int		open_flags;

	node = cmd->outputs;
	while (node)
	{
		output_file = (t_file *)node->content;
		open_flags = O_WRONLY | O_TRUNC | O_CREAT;
		if (output_file->is_extra)
			open_flags = O_WRONLY | O_APPEND | O_CREAT;
		cmd->out_redir_fd = open_file(output_file->name, open_flags);
		if (cmd->out_redir_fd == -1)
		{
			g_exit_status = 1;
			break ;
		}
		if (node->next)
			close(cmd->out_redir_fd);
		node = node->next;
	}
}
 
// out_redir_fd is set to	-1 if the redirection was invalid - means dont run the cmd
//							0 if there is no output redir for this chunk - means run the cmd but dont dup anything to the pipe, use the pipes as they are
//							> 0 if it is a valid redirection
void	redirect_output(t_cmd_chunk **cmds)
{
	int		i;

	i = -1;
	while (cmds[++i])
	{
		cmds[i]->out_redir_fd = -1;
		if (cmds[i]->in_redir_fd != -1)
		{
			if (cmds[i]->outputs && !(cmds[i]->outputs->content))
			{
				// if (!cmds[i + 1]) // is the last command
				// 	cmds[i]->out_redir_fd = STDOUT_FILENO;
				// else
					cmds[i]->out_redir_fd = 0;
			}
			else
				open_op_files(cmds[i]);
		}
	}
}
