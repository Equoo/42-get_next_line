/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:17:33 by dderny            #+#    #+#             */
/*   Updated: 2024/11/20 11:53:23y dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdint.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*array;
	size_t	*intarray;

	STARTTIME("calloc");
	i = 0;
	array = NULL;
	if ((unsigned long long)nmemb * (unsigned long long)size > SIZE_MAX)
		return (NULL);
	array = malloc(nmemb * size);
	if (array)
	{
		intarray = (size_t *)array;
		while (i < (nmemb * size) / sizeof(i))
			intarray[i++] = 0;
		i = i * sizeof(i);
		while (i < nmemb * size)
			((char *)array)[i++] = 0;
	}
	ENDTIME("calloc");
	return (array);
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

#include <string.h>
size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	src_len;

	STARTTIME("strlcpy");
	src_len = ft_strlen(src);
	if (!src_len)
		return (0);
	i = 0;
	/* while (i < src_len / sizeof(src_len) && i < n / sizeof(src_len))
	{
		__builtin_printf("%ld, %ld\n", src_len, i);
		((size_t *)dest)[i] = ((size_t *)src)[i];
		i++;
	}
	i = i * sizeof(src_len); */
	while (src[i] && i + 1 < n)
	{
		dest[i] = src[i];
		i++;
	}
	__builtin_printf("UH %ld, %ld, %ld, %ld\n", strlen(src), src_len, n, i);
	if (n)
		dest[i] = 0;
	ENDTIME("strlcpy");
	return (src_len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	destlen;
	size_t	srclen;

	STARTTIME("strlcat");
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
	ENDTIME("strlcat");
	return (destlen + srclen);
}

size_t	ft_strlen(const char *str)
{
	size_t	s_int;
	size_t	*int_str;
	int		i;

	if (!*str)
		return (0);
	int_str = (size_t *)str;
	while (*int_str)
	{
		s_int = *int_str++;
		if ((s_int - HAS_ZERO_MASK) & ~s_int & HAS_ZERO_MASKN)
		{
			i = -1;
			s_int = 0;
			while (++i < (int)sizeof(s_int))
				if ((const char *)(int_str - 1)[i] == 0)
					s_int = (void *)(int_str - 1) - (void *)str + i;
			if (s_int)
				return (s_int);
		}
	}
	return ((const char *)int_str - str);
}
