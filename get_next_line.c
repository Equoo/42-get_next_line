/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:25:54 by dderny            #+#    #+#             */
/*   Updated: 2024/12/07 15:32:56 by dderny           ###   ########.fr       */
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
	if (!data->buf[data->pos])
		line = read_line(&datafd, NULL);
	else
		line = read_buffer(&datafd);
	if (!line)
	{
		data = (t_gnl_data){.state = GNL_UNUSED, .pos = 0, .fd = 0}
		//data->buf[0] = 0;
	}
	return (line);
}

char	*read_line(t_gnl_data *data, char *buffer)
{
	t_gnl_data rdta;

	data->state = GNL_INUSE;
	while (data->state != GNL_ENDED && !rdta->newline && (!buffer || (buffer
				&& buffer[0] != '\n')))
		buffer = read_until_newline(data, buffer, );
	if (!buffer)
		return (NULL);
	if (len == BUFFER_SIZE)
		data->states[fd] = 1;
	if (buffer && (BUFFER_SIZE != 1))
	{
		ft_strlcpy(data->bufs[fd], buffer + data->newline + 1, BUFFER_SIZE + 1);
		data->bufs[fd][data->total - data->newline - 1] = 0;
		if (data->newline || buffer[0] == '\n')
			buffer[data->newline + 1] = 0;
	}
	else
		data->states[fd] = 2;
	data->pos[fd] = 0;
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
		data->states[data->fd] = 2;
	else
		data->newline = get_newline(buffer);
	data->state = GNL_INUSE;
	return (buffer);
}

char	*read_buffer(t_gnl_data *data)
{
	char	*stored;
	char	*buffer;

	buffer = NULL;
	stored = data->bufs[data->fd] + data->pos[data->fd];
	data->newline = get_newline(data->bufs[data->fd] + data->pos[data->fd]);
	data->total = data->newline + 1;
	if (!data->newline && stored[0] != '\n')
		data->total = ft_strlen(stored);
	buffer = ft_calloc(data->total + 9, sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, stored, data->total + 1);
	if (data->newline || !data->states[data->fd] || stored[0] == '\n')
		data->pos[data->fd] = data->pos[data->fd] + data->total;
	else
		return (read_line(data->fd, data, buffer));
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

// #include <fcntl.h>

// int	main(void)
// {
// 	char	*test3;
// 	int		fd3;
// 	int		i;
// 	char	*tmp3;

// 	test3 = NULL;
// 	// char *test5 = NULL;
// 	test3 = ft_calloc(1, 1);
// 	// test5 = ft_calloc(1, 1);
// 	fd3 = open("test_1.txt", O_RDONLY);
// 	i = 0;
// 	while (1)
// 	{
// 		i++;
// 		tmp3 = get_next_line(fd3);
// 		// if (tmp)
// 		//	test1 = ft_strjoin(test1, tmp);
// 		// if (tmp2)
// 		//	test2 = ft_strjoin(test2, tmp2);
// 			__builtin_printf("%s", tmp3);
// 		if (tmp3)
// 		{
// 			free(tmp3);
// 			// test3 = ft_strjoin(test3, tmp3);
// 		}
// 		else
// 			break ;
// 	}
// 	close(fd3);
// 	free(test3);
// 	return (0);
// }

// /* 	i = 0;
// 		while (i < 3)
// 		{
// 			i++;
// 			char *tmp = get_next_line(0);
// 			if (tmp)
// 				test5 = ft_strjoin(test5, tmp);
// 			else
// 				break ;
// 		} */
// //__builtin_printf("sayedto: %s\n", test5);