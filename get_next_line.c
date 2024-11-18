/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:17:33 by dderny            #+#    #+#             */
/*   Updated: 2024/11/18 18:01:17 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static t_gnl_data	data;

	if (fd < 0)
		return (NULL);
	if (!*data.bufs[fd])
		read_line(fd, &data);
	return ();
}


char	*read_line(int fd, t_gnl_data *data)
{
	ssize_t		total;
	ssize_t		len;
	char	*buffer;
	char	*last;
	
	len = 0;
	total = 0;
	while (!len || (!get_newline(buffer, len) && len = BUFFER_SIZE))
	{
		buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!buffer)
			return (NULL);
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1)
			return (NULL);
		if (!len)
			break ;
	}
    return (buffer);
}

int	get_newline(char *str, ssize_t len)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] != '\n')
		return (0);
	return (1);
}







char	*get_next_line(int fd)
{
	static t_gnl_data	data;
	char				*buffer;
	long long int		len;

	len = 0;
	buffer = NULL;
	if (!fd)
	{
		if (data.fd_states[0] == 3)
			len = get_next_line_file(0, buffer);
		else if (*data.last)
			return (get_line_from_last(&data));
		else
			len = get_next_line_stdin(&data, buffer);
	}
	else
		len = get_next_line_file(fd, buffer);
	if (len == -1 || !buffer[0] || data.fd_states[fd])
	{
		data.fd_states[fd] = 0;
		return (NULL);
	}
	if (buffer[len - 1] != '\n')
		data.fd_states[fd] = 1;
	return (get_from_len(len, buffer, 1));
}

char	*get_line_from_last(t_gnl_data *data)
{
	size_t	len;
	char	*line;

	len = 1;
	while (data->last[len] && data->last[len] != '\n')
		len++;
	if (data->last[len] == '\n')
		len++;
	if (!data->last[len] && data->fd_states[0] == 2)
	{
		data->fd_states[0] = 3;
		return (get_next_line_stdin_file(data, len));
	}
	line = get_from_len(len, data->last, 0);
	if (!line)
		return (NULL);
	if (data->last[len])
		ft_strlcpy(data->last, data->last + len, BUFFER_SIZE);
	return (line);
}

char	*get_next_line_stdin_file(t_gnl_data *data, size_t len)
{
	char	*buffer;
	int		total;

	buffer = NULL;
	total = get_next_line_file(0, buffer);
	if (total == -1 || !total || len)
		return (NULL);
	if (buffer[total - 1] != '\n')
		data->fd_states[0] = 1;
	return (buffer);
}

char	*get_from_len(size_t len, char *buffer, int ismalloc)
{
	char	*line;

	line = ft_calloc(len, sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, len);
	if (ismalloc)
		free(buffer);
	return (line);
}

long long int	get_next_line_file(int fd, char *buffer)
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
	if (!i)
	{
		free(buffer);
		return (-1);
	}
	return (i);
}

long long int	get_next_line_stdin(t_gnl_data *data, char *buffer)
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
	if (buffer[BUFFER_SIZE - 1])
		data->fd_states[0] = 2;
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
	int fd3 = open("bible.txt", O_RDONLY);
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