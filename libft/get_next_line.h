/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 19:28:34 by ttresori          #+#    #+#             */
/*   Updated: 2017/08/31 20:01:47 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>

# define BUFF_SIZE 32

typedef	struct	s_gnl
{
	char		buf[BUFF_SIZE + 1];
	char		*cpy;
	char		*t;
	char		*rest[1000];
	int			ret;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
