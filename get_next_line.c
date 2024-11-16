/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:17:33 by dderny            #+#    #+#             */
/*   Updated: 2024/11/16 18:17:33 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char    *get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	c[1];
	int		i;

	s[0] = 1;
	s[1] = 0;
	i = 0;
	while (c[0] && i < BUFFER_SIZE)
	{
		if (read(fd, c, 1) )
	}
}