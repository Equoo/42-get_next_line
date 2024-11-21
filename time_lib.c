#include "get_next_line.h"
#include "time_lib.h"
#include <stdlib.h>
#include <time.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n
		&& (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	if (i == n)
		return (0);
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

size_t	time_strlen(const char *str)
{
	const char	*const_str;

	const_str = str;
	while (*const_str != '\0')
		++const_str;
	return (const_str - str);
}

t_timehook	**gettimehooks(void)
{
	static t_timehook	*hooks;

	return (&hooks);
}

void	*time_calloc(size_t nmemb, size_t size)
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

t_timehook	*gethookbyid(char *id)
{
	t_timehook	**hooks;
	t_timehook	*hook;
	size_t		len;

	hooks = gettimehooks();
	hook = *hooks;
	len = time_strlen(id);
	while (hook && ft_strncmp(hook->id, id, len))
	{	
		if (!hook->next)
			break ;
		hook = hook->next;
	}
	if (!hook || (hook && ft_strncmp(hook->id, id, len)))
	{
		if (*hooks)
		{
			hook->next = time_calloc(1, sizeof(t_timehook));
			hook = hook->next;
		}
		else
		{
			*hooks = time_calloc(1, sizeof(t_timehook));
			hook = *hooks;
		}
		if (!hook)
			return (NULL);
		if (!*hooks)
			*hooks = hook;
		hook->total = 0;
		hook->id = id;
	}
	return (hook);
}

int	starttime(char *id)
{
	t_timehook	*hook;

	hook = gethookbyid(id);
	if (!hook)
		return (0);
	hook->start = clock();
	return (1);
}

int	endtime(char *id)
{
	t_timehook	*hook;

	hook = gethookbyid(id);
	if (!hook)
		return (0);
	hook->total += ((double)(clock() - hook->start)) / CLOCKS_PER_SEC;
	return (1);
}

void	printtimes(void)
{
	t_timehook	**hooks;
	t_timehook	*hook;
	t_timehook	*last;

	hooks = gettimehooks();
	hook = *hooks;
	while (hook)
	{
		__builtin_printf("%s: %f\n", hook->id, hook->total);
		last = hook;
		hook = hook->next;
		free(last);
	}
}
