/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_lib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:33:30 by dderny            #+#    #+#             */
/*   Updated: 2024/11/20 10:59:11 by dderny           ###   ########.fr       */
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

t_timehook				**GETTIMEHOOKS(void);
t_timehook				*GETHOOKBYID(char *id);
int						STARTTIME(char *id);
int						ENDTIME(char *id);
void					PRINTTIMES(void);

#endif