/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_lib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:33:30 by dderny            #+#    #+#             */
/*   Updated: 2024/11/21 13:36:49 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_LIB_H
# define TIME_LIB_H
# include <time.h>

typedef struct s_timehook
{
	char				*id;
	clock_t				start;
	double				total;
	struct s_timehook	*next;
}						t_timehook;

t_timehook				**gettimehooks(void);
t_timehook				*gethookbyid(char *id);
int						starttime(char *id);
int						endtime(char *id);
void					printtimes(void);

#endif