/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:17:33 by dderny            #+#    #+#             */
/*   Updated: 2024/11/18 16:39:06 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl_data
{
	char	bufs[4096][BUFFER_SIZE];
}			t_gnl_data;

char		*get_next_line(int fd);

char		*get_line_from_last(t_gnl_data *data);

char		*get_next_line_stdin_file(t_gnl_data *data, size_t len);

char		*get_from_len(size_t len, char *buffer, int ismalloc);

long long int		get_next_line_file(int fd, char *buffer);

long long int		get_next_line_stdin(t_gnl_data *data, char *buffer);

void		*ft_calloc(size_t nmemb, size_t size);

char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlcpy(char *dest, const char *src, size_t n);
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dest, const char *src, size_t n);

#endif
