/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 22:04:19 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/21 23:03:16 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_aux(t_philo *philo, long int time, char action)
{
	printf("\033[3%im", (philo->p_num) % 5 + 2);
	if (action == 'f')
		printf("%ld    %d has taken a fork\n", time, philo->p_num);
	else if (action == 'e')
		printf("%ld    %d is eating\n", time, philo->p_num);
	else if (action == 's')
		printf("%ld    %d is sleeping\n", time, philo->p_num);
	else if (action == 't')
		printf("%ld    %d is thinking\n", time, philo->p_num);
	else
	{
		printf("\033[31m%ld    %d died\n", time, philo->p_num);
		philo->table->some_die = 1;
	}
	printf("\033[0m");
}

void	print_actions(t_philo *philo, char action)
{
	long int	time;

	pthread_mutex_lock(&philo->table->print);
	if (!(philo->table->some_die))
	{
		time = m_time() - philo->table->start;
		print_aux(philo, time, action);
	}
	pthread_mutex_unlock(&philo->table->print);
}
