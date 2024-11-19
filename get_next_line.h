/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:17:33 by dderny            #+#    #+#             */
/*   Updated: 2024/11/19 17:49:45 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE = 4096
# endif
typedef struct s_gnl_data
{
	char	bufs[4096][BUFFER_SIZE];
	int		states[4096];
}			t_gnl_data;

char		*get_next_line(int fd);

char		*read_line(int fd, char *buffer, t_gnl_data *data, size_t *total);

char		*read_until_newline(int fd, size_t *newline, char *buffer, size_t *total, t_gnl_data *data);

char		*read_buffer(int fd, t_gnl_data *data, size_t *total);

size_t		get_newline(char *str);



void		*ft_calloc(size_t nmemb, size_t size);

char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlcpy(char *dest, const char *src, size_t n);
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dest, const char *src, size_t n);

#endif
