/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:25:43 by dderny            #+#    #+#             */
/*   Updated: 2024/12/12 18:01:24 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
//# include "malloc_bonus.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define MAX_FILES 128

# define HAS_ZERO_MASK 0x1010101010101010
# define HAS_ZERO_MASKN 0x8080808080808080

typedef enum e_gnl_state
{
	GNL_UNUSED,
	GNL_INUSE,
	GNL_JSP,
	GNL_ENDED,
}				t_gnl_state;

typedef struct s_gnl_read
{
	size_t		total;
	size_t		newline;
	ssize_t		len;
	char		*last;
}				t_gnl_read;

typedef struct s_gnl_data
{
	char		buf[BUFFER_SIZE + 1];
	size_t		pos;
	t_gnl_state	state;
	int			fd;
}				t_gnl_data;

char			*get_next_line(int fd);

char			*read_line(t_gnl_data *data, char *buffer);
char			*read_until_newline(t_gnl_data *data, char *buffer,
					t_gnl_read *rdta);
char			*read_buffer(t_gnl_data *data);

size_t			get_newline(char *str);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlcpy(char *dest, const char *src, size_t n);
size_t			ft_strlen(const char *str);
size_t			ft_strlcat(char *dest, const char *src, size_t n);

#endif
