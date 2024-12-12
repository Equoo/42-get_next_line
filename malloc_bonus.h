/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:57:02 by dderny            #+#    #+#             */
/*   Updated: 2024/12/12 17:57:40 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MALLOC_BONUS_H
# define MALLOC_BONUS_H
void	*my_malloc(size_t size);
# define malloc(size) my_malloc(size)
#endif