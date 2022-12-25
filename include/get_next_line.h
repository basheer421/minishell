/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 21:43:41 by mfirdous          #+#    #+#             */
/*   Updated: 2022/08/04 20:16:53 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# ifdef _WIN32
#  include <io.h>
# else
#  include <unistd.h>
# endif

char	*get_next_line(int fd);
int		read_block(int fd, char **buf);
int		has_new_line(char *buf);
char	*ft_strndup(const char *s, int n);
char	*ft_strnjoin(char **buf, char **new_block);
char	*get_line(char **buf, int bytes_read, int line_len);

#endif