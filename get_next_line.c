/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:17:33 by dderny            #+#    #+#             */
/*   Updated: 2024/11/18 00:40:53 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static t_gnl_data	data;
	char				*buffer;
	size_t				len;

	len = 0;
	if (!fd)
	{
		if (*data.last)
			return (get_last_line(&data));
		else
			len = get_next_line_stdin(&data, buffer);
	}
	else
		len = get_next_line_file(fd, buffer);
	if (!buffer[0] || data.fd_states[fd] || len == -1)
	{
		data.fd_states[fd] = 0;
		return (NULL);
	}
	if (buffer[len - 1] != '\n')
		data.fd_states[fd] = 1;
	return (get_from_len(len, buffer));
}

char	*get_last_line(t_gnl_data *data)
{

	return ()
}

char	*get_from_len(size_t len, char *buffer)
{
	char	*line;

	line = ft_calloc(len, sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, len);
	free(buffer);
	return (line);
}

size_t	get_next_line_other(int fd, char *buffer)
{
	int	i;
	int	len;

	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (-1);
	i = 0;
	while (i < BUFFER_SIZE - 1 && (!i || (buffer[i - 1] && (unsigned int)buffer[i - 1] != '\n')))
	{
		len = read(fd, buffer + i, 1);
		if (len == -1)
			return (-1);
		if (!len)
			break ;
		i++;
	}
	return (i);
}

size_t	get_next_line_stdin(t_gnl_data *data, char *buffer)
{
	int	i;
	int	len;

	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (-1);
	len = read(0, buffer, BUFFER_SIZE);
	if (len == -1)
		return (-1);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n' && i + 1 != len)
	{
		ft_strlcpy(data->last, buffer + i + 1, BUFFER_SIZE);
		buffer[i + 1] = 0;
		return (i + 1);
	}
	return (len);
}


char	*get_next_line(int fd)
{
	static char	last[BUFFER_SIZE + 1];
	char		*buffer;
	int			len;
	int			i;

	if (!fd && ft_strlen(last) > 1)
	{
		if (*last == '1')
		{
			last[0] = '0';
			last[1] = 0;
			return (NULL);
		}
		i = 1;
		while (last[i] && last[i] != '\n')
			i++;
		buffer = ft_calloc(i, sizeof(char));
		if (!buffer)
			return (NULL);
		ft_strlcpy(buffer, last + 1, i + 1);
		if (!last[i])
		{
			last[0] = '1';
			last[1] = 0;
		}
		else
		{
			ft_strlcpy(last + 1, last + i + 1, BUFFER_SIZE);
			last[0] = '0';
		}
		
		return (buffer);
	}
	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd)
	{
		i = 0;
		while (i < BUFFER_SIZE - 1 && (!i || (buffer[i - 1] && (unsigned int)buffer[i - 1] != '\n')))
		{
			len = read(fd, buffer + i, 1);
			if (len == -1)
				return (NULL);
			if (!len)
				break ;
			i++;
		}
	}
	else
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1)
			return (NULL);
		i = 0;
		while (buffer[i])
		{
			if (buffer[i] == '\n' && i + 1 != len)
			{
				last[0] = '0';
				ft_strlcpy(last + 1, buffer + i + 1, BUFFER_SIZE);
				buffer[i + 1] = 0;
				return (buffer);
			}
			i++;			
		}
		if (buffer[0] && buffer[len - 1] != '\n')
		{
			last[0] = '1';
			last[1] = 0;
		}
	}
	if (!buffer[0])
		return (NULL);
	return (buffer);
}

#include <fcntl.h>
int	main()
{
	char *test1 = NULL;
	char *test2 = NULL;
	char *test3 = NULL;
	char *test4 = NULL;
	char *test5 = NULL;
	test1 = ft_calloc(1, 1);
	test2 = ft_calloc(1, 1);
	test3 = ft_calloc(1, 1);
	test4 = ft_calloc(1, 1);
	test5 = ft_calloc(1, 1);

	int fd2 = open("test_2.txt", O_RDONLY);
	int fd1 = open("test_1.txt", O_RDONLY);
	int fd3 = open("test_3.txt", O_RDONLY);
	int i = 0;
	while (1)
	{
		i++;
		char *tmp = get_next_line(fd1);
		char *tmp2 = get_next_line(fd2);
		char *tmp3 = get_next_line(fd3);
		
		if (i == 3)
		{
			while (1)
			{
				char *tmpf = get_next_line(0);
				if (tmpf)
					test4 = ft_strjoin(test4, tmpf);
				else
					break;
			}
			__builtin_printf("sayed:\n%s\n\n", test4);
			i = 1000;
		}
		
		if (tmp)
			test1 = ft_strjoin(test1, tmp);
		if (tmp2)
			test2 = ft_strjoin(test2, tmp2);
		if (tmp3)
			test3 = ft_strjoin(test3, tmp3);
		if (!tmp && !tmp2 && !tmp3)
			break ;
	}
	__builtin_printf("%s\n\n", test1);
	__builtin_printf("%s\n\n", test2);
	__builtin_printf("%s\n\n", test3);
	close(fd1);
	close(fd2);
	close(fd3);

	i = 0;
	while (i < 3)
	{
		i++;
		char *tmp = get_next_line(0);
		if (tmp)
			test5 = ft_strjoin(test5, tmp);
		else
			break;
	}
	__builtin_printf("sayedto: %s\n", test5);
	return (0);
}