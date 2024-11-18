/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:17:33 by dderny            #+#    #+#             */
/*   Updated: 2024/11/17 21:42:25 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl_data
{
	int		*fd_states[BUFFER_SIZE];
	char	last[BUFFER_SIZE];
}			t_gnl_data;

char		*get_next_line(int fd);

void		*ft_calloc(size_t nmemb, size_t size);

char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlcpy(char *dest, const char *src, size_t n);
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dest, const char *src, size_t n);

#endif
