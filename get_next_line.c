/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:25:54 by dderny            #+#    #+#             */
/*   Updated: 2024/11/22 19:35:16 by dderny           ###   ########.fr       */
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
	if (data.states[fd] == 2)
		return (NULL);
	else if (!data.bufs[fd][data.pos[fd]])
		line = read_line(fd, NULL, &data, &total);
	else
		line = read_buffer(fd, &data, &total);
	return (line);
}

char	*read_line(int fd, char *buffer, t_gnl_data *data, size_t *total)
{
	size_t	newline;

	newline = 0;
	data->states[fd] = 0;
	buffer = read_until_newline(fd, &newline, buffer, total, data);
	if (buffer && (BUFFER_SIZE != 1) /* && newline != *total - 1 */)
	{
		ft_strlcpy(data->bufs[fd], buffer + newline + 1, BUFFER_SIZE + 1);
		data->bufs[fd][*total - newline - 1] = 0;
		if (newline || buffer[0] == '\n')
			buffer[newline + 1] = 0;
		if (*total % BUFFER_SIZE != 0)
			data->states[fd] = 2;
	}
	else
		data->states[fd] = 2;
	data->pos[fd] = 0;
	return (buffer);
}

char	*read_until_newline(int fd, size_t *newline, char *buffer,
		size_t *total, t_gnl_data *data)
{
	ssize_t	len;
	char	*last;

	len = 0;
	while ((!len && !*total) || (!*newline && buffer && buffer[0] != '\n'
			&& len == BUFFER_SIZE))
	{
		last = buffer;
		buffer = ft_calloc(BUFFER_SIZE + 9, sizeof(char));
		if (!buffer)
			return (NULL);
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1 || (!len && !*total)) // return seulement si len 0 mais si aussi on a deja compte
			return (free(buffer), NULL);
		*total = *total + (size_t)len;
		if (last)
			buffer = ft_strjoin(last, buffer);
		if (!buffer)
			return (NULL);
		*newline = get_newline(buffer);
	}
	if (len == BUFFER_SIZE)
		data->states[fd] = 1;
	return (buffer);
}

char	*read_buffer(int fd, t_gnl_data *data, size_t *total)
{
	const size_t	newline = get_newline(data->bufs[fd] + data->pos[fd]);
	char			*stored;
	char			*buffer;

	// char			*tmp;
	buffer = NULL;
	stored = data->bufs[fd] + data->pos[fd];
	*total = newline + 1;
	if (!newline && stored[0] != '\n')
		*total = ft_strlen(stored);
	buffer = ft_calloc(*total + 9, sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, stored, *total + 1);
	if (newline || !data->states[fd] || stored[0] == '\n')
		data->pos[fd] = data->pos[fd] + *total;
	else
		return (read_line(fd, buffer, data, total));
	//__builtin_printf("-- %s", buffer);
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
	char *test3 = NULL;
	// char *test5 = NULL;
	test3 = ft_calloc(1, 1);
	// test5 = ft_calloc(1, 1);

	int fd3 = open("test_1.txt", O_RDONLY);
	int i = 0;
	while (1)
	{
		i++;
		char *tmp3 = get_next_line(fd3);

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
			__builtin_printf("\nsayed:\n%s\n\n", test4);
			i = 1000;
		} */

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
	//__builtin_printf("%s", test3);

	free(test3);
	close(fd3);

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