/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:08:49 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/11 18:01:00 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long int	str_to_long(char *nptr)
{
	long int	number;
	int			i;

	i = -1;
	number = 0;
	while (*(nptr + ++i))
		number = (number * 10) + (*(nptr + i) - '0');
	return (number);
}

long int	m_time(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	m_sleep(long int time)
{
	usleep(time * 1000);
}