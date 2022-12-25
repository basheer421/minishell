/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:30:21 by bammar            #+#    #+#             */
/*   Updated: 2022/12/25 20:23:23 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "pipex.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//		* Getting the line *
int		ms_line_read(const char *prompt);

//		* Checking line errors and returns 1 if it has at least one command to be excuted
//			otherwise 0 on error *
// int		ms_line_contains_commands(char *line);

//		* Execute the valid commands in parallel as minishell requires only that
// int		ms_line_execute_commands(char *line);


#endif
