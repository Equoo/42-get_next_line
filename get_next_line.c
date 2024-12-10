/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:25:54 by dderny            #+#    #+#             */
/*   Updated: 2024/12/10 15:06:30 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

t_gnl_data 	*getfddata(int fd)
{
	static t_gnl_data	data[MAX_FILES];
	int	i;

	if (fd < 0)
		return (NULL);
	i = 0;
	while (i < MAX_FILES && data[i].fd != fd)
		i++;
	if (i == MAX_FILES)
	{
		i = 0;
		while (data[i].state != GNL_UNUSED)
			i++;
		if (i == MAX_FILES)
			return (NULL);
		data[i] = (t_gnl_data){.fd = fd, .state = GNL_INUSE};
	}
	return (&data[i]);
}

char	*get_next_line(int fd)
{
	t_gnl_data			*data;
	char				*line;

	data = getfddata(fd);
	if (!data)
		return (NULL);
	line = NULL;
	if (data->state != GNL_ENDED && !data->buf[data->pos])
		line = read_line(data, NULL);
	else if (data->state != GNL_ENDED)
		line = read_buffer(data);
	if (!line)
		*data = (t_gnl_data){.state = GNL_UNUSED, .pos = 0, .fd = 0};
	return (line);
}

char	*read_line(t_gnl_data *data, char *buffer)
{
	t_gnl_read rdta;

	rdta = (t_gnl_read){.last = NULL};
	if (buffer)
		rdta.total = ft_strlen(buffer);
	data->state = GNL_INUSE;
	while (data->state != GNL_ENDED && !rdta.newline && (!buffer || (buffer
				&& buffer[0] != '\n')))
		buffer = read_until_newline(data, buffer, &rdta);
	if (!buffer)
		return (NULL);
	if (rdta.len == BUFFER_SIZE)
		data->state = GNL_JSP;
	if (BUFFER_SIZE != 1)
	{
		ft_strlcpy(data->buf, buffer + rdta.newline + 1, BUFFER_SIZE + 1);
		data->buf[rdta.total - rdta.newline - 1] = 0;
		if (rdta.newline || buffer[0] == '\n')
			buffer[rdta.newline + 1] = 0;
	}
	data->pos = 0;
	return (buffer);
}

char	*read_until_newline(t_gnl_data *data, char *buffer, t_gnl_read *rdta)
{
	data->state = GNL_ENDED;
	rdta->last = buffer;
	buffer = ft_calloc(BUFFER_SIZE + 9, sizeof(char));
	if (!buffer)
		return (NULL);
	rdta->len = read(data->fd, buffer, BUFFER_SIZE);
	if (!rdta->len || rdta->len == -1)
	{
		if (rdta->len == -1 && rdta->last)
			free(rdta->last);
		return (free(buffer), rdta->last);
	}
	rdta->total += (size_t)rdta->len;
	if (rdta->last)
		buffer = ft_strjoin(rdta->last, buffer);
	if (!buffer)
		return (NULL);
	rdta->newline = get_newline(buffer);
	data->state = GNL_INUSE;
	return (buffer);
}

char	*read_buffer(t_gnl_data *data)
{
	t_gnl_read rdta;
	char	*buffer;

	rdta = (t_gnl_read){.last = NULL};
	buffer = NULL;
	rdta.last = data->buf + data->pos;
	rdta.newline = get_newline(rdta.last);
	rdta.total = rdta.newline + 1;
	if (!rdta.newline && rdta.last[0] != '\n')
		rdta.total = ft_strlen(rdta.last);
	buffer = ft_calloc(rdta.total + 9, sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, rdta.last, rdta.total + 1);
	if (rdta.newline /* || data->state == GNL_INUSE */ || rdta.last[0] == '\n')
		data->pos = data->pos + rdta.total;
	else
		return (read_line(data, buffer));
	return (buffer);
}

size_t	get_newline(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (unsigned char)str[i] != '\n')
		i++;
	if ((unsigned char)str[i] != '\n')
		return (0);
	return (i);
}

#include <fcntl.h>

int	main(void)
{
	char	*test3;
	int		fd3;
	int		i;
	char	*tmp3;

	test3 = NULL;
	// char *test5 = NULL;
	test3 = ft_calloc(1, 1);
	// test5 = ft_calloc(1, 1);
	fd3 = open("test_4.txt", O_RDONLY);
	i = 0;
	while (1)
	{
		i++;
		tmp3 = get_next_line(fd3);
		// if (tmp)
		//	test1 = ft_strjoin(test1, tmp);
		// if (tmp2)
		//	test2 = ft_strjoin(test2, tmp2);
		if (tmp3)
		{
			__builtin_printf("%s", tmp3);
			free(tmp3);
			// test3 = ft_strjoin(test3, tmp3);
		}
		else
			break ;
	}
	close(fd3);
	free(test3);
	return (0);
}

/* 	i = 0;
		while (i < 3)
		{
			i++;
			char *tmp = get_next_line(0);
			if (tmp)
				test5 = ft_strjoin(test5, tmp);
			else
				break ;
		} */
//__builtin_printf("sayedto: %s\n", test5);