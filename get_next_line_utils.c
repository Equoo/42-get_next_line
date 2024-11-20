/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:17:33 by dderny            #+#    #+#             */
/*   Updated: 2024/11/20 11:53:23 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*array;

	i = 0;
	array = NULL;
	if ((unsigned long long)nmemb * (unsigned long long)size > SIZE_MAX)
		return (NULL);
	array = malloc(nmemb * size);
	if (array)
	{
		while (i < nmemb * size)
			((char *)array)[i++] = 0;
	}
	return (array);
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



char	*ft_strjoin(char *s1, char *s2)
{
	size_t	total;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_calloc(total, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, total);
	ft_strlcat(str, s2, total);
	free(s1);
	free(s2);
	return (str);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < n)
	{
		dest[i] = src[i];
		i++;
	}
	if (n)
		dest[i] = 0;
	return ((size_t)ft_strlen(src));
}

size_t	ft_strlen(const char *str)
{
	const char	*const_str;

	STARTTIME("strlen");
	const_str = str;
	while (*const_str != '\0')
		++const_str;
	ENDTIME("strlen");
	return (const_str - str);
}

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	destlen;
	size_t	srclen;

	i = 0;
	j = 0;
	srclen = ft_strlen(src);
	if (!n)
		return (srclen);
	while (dest[i])
		i++;
	destlen = i;
	if (destlen >= n)
		return (srclen + n);
	while (src[j] && i + 1 < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = 0;
	return (destlen + srclen);
}