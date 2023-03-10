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
		cmd->out_fd = open_file(output_file->name, open_flags);
		if (cmd->out_fd == -1)
		{
			g_exit_status = 1;
			break ;
		}
		if (node->next)
			close(cmd->out_fd);
		node = node->next;
	}
}

void	redirect_output(t_cmd_chunk **cmds)
{
	int		i;

	i = -1;
	while (cmds[++i])
	{
		cmds[i]->out_fd = -1;
		if (cmds[i]->in_fd != -1)
		{
			if (cmds[i]->outputs && !(cmds[i]->outputs->content))
				cmds[i]->out_fd = 0;
			else
				open_op_files(cmds[i]);
		}
	}
}
