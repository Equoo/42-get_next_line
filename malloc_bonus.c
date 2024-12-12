/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:57:04 by dderny            #+#    #+#             */
/*   Updated: 2024/12/12 17:57:12 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*my_malloc(size_t size)
{
	static int	counter = 0;

	counter++;
	if (counter == 5)
	{
		return (NULL);
	}
	return (malloc(size));
}
