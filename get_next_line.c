/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:17:33 by dderny            #+#    #+#             */
/*   Updated: 2024/11/19 18:09:50 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static t_gnl_data	data;
	char				*line;
	size_t				total;

	if (fd < 0)
		return (NULL);
	total = 0;
	line = NULL;
	if (!*data.bufs[fd])
		line = read_line(fd, NULL, &data, &total);
	else
		line = read_buffer(fd, &data, &total);
	return (line);
}

char	*read_line(int fd, char *buffer, t_gnl_data *data, size_t *total)
{
	size_t	newline;

	newline = 0;
	buffer = read_until_newline(fd, &newline, buffer, total, data);
	if (buffer && newline != *total - 1)
	{
		ft_strlcpy(data->bufs[fd], buffer + newline + 1, BUFFER_SIZE);
		buffer[newline + 1] = 0;
	}
	return (buffer);
}

char	*read_until_newline(int fd, size_t *newline, char *buffer, size_t *total, t_gnl_data *data)
{
	ssize_t	len;
	char	*last;
	
	len = 0;
	while (!len || (!*newline && len == BUFFER_SIZE))
	{
		last = buffer;
		buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!buffer)
			return (NULL);
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1 || !len)
			return (NULL);
		*total = *total + (size_t)len;
		if (last)
			buffer = ft_strjoin(last, buffer);
		*newline = get_newline(buffer);
	}
	if (len == BUFFER_SIZE)
		data->states[fd] = 1;	
	return (buffer);
}

char	*read_buffer(int fd, t_gnl_data *data, size_t *total)
{
	char	*buffer;
	size_t	newline;

	buffer = NULL;
	newline = get_newline(data->bufs[fd]);
	if (!newline)
		newline = ft_strlen(data->bufs[fd]) - 1;	
	buffer = ft_calloc(newline + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, data->bufs[fd], newline + 1);
	if (newline || !data->states[fd])	
		ft_strlcpy(data->bufs[fd], data->bufs[fd] + newline + 1, BUFFER_SIZE);
	else
	{
		buffer = read_line(fd, buffer, data, total);	
		data->bufs[fd][0] = 0;
	}
	return (buffer);
}


#include <fcntl.h>

int	main(void)
{
	char *test1 = NULL;
	char *test2 = NULL;
	//char *test3 = NULL;
	//char *test4 = NULL;
	//char *test5 = NULL;
	test1 = ft_calloc(1, 1);
	test2 = ft_calloc(1, 1);
	//test3 = ft_calloc(1, 1);
	//test4 = ft_calloc(1, 1);
	//test5 = ft_calloc(1, 1);

	int fd2 = open("test_2.txt", O_RDONLY);
	int fd1 = open("test_1.txt", O_RDONLY);
	//int fd3 = open("bible.txt", O_RDONLY);
	int i = 0;
	while (1)
	{
		i++;
		char *tmp = get_next_line(fd1);
		char *tmp2 = get_next_line(fd2);
		//char *tmp3 = get_next_line(fd3);

		/* if (i == 3)
		{
			while (1)
			{
				char *tmpf = get_next_line(0);
				if (tmpf)
					test4 = ft_strjoin(test4, tmpf);
				else
					break ;
			}
			__builtin_printf("sayed:\n%s\n\n", test4);
			i = 1000;
		} */

		if (tmp)
			test1 = ft_strjoin(test1, tmp);
		if (tmp2)
			test2 = ft_strjoin(test2, tmp2);
		//if (tmp3)
		//	test3 = ft_strjoin(test3, tmp3);
		if (!tmp && !tmp2 /* && !tmp3 */)
			break ;
	}
	__builtin_printf("%s\n\n", test1);
	__builtin_printf("%s\n\n", test2);
	//__builtin_printf("%s\n\n", test3);
	close(fd1);
	close(fd2);
	//close(fd3);

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
	return (0);
}