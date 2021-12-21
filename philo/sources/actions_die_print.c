/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_die_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:48:18 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/21 18:27:19 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_die(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (!(philo->table->some_die))
	{
		if (philo->table->n_lunch && philo->n_eats == philo->table->n_lunch)
			break ;
		if (philo->table->time_d < m_time() - philo->last_eat)
			print_actions(philo, 'd');
	}
	i = -1;
	while (++i < philo->table->n_phis)
		pthread_mutex_unlock(philo->table->forks + i);
	return (NULL);
}

static void	print_aux(t_philo *philo, long int time, int p_num, char action)
{
	printf("\033[3%im", p_num % 5 + 2);
	if (action == 'f')
		printf("%ld    %d has taken a fork\n", time, p_num);
	else if (action == 'e')
		printf("%ld    %d is eating\n", time, p_num);
	else if (action == 's')
		printf("%ld    %d is sleeping\n", time, p_num);
	else if (action == 't')
		printf("%ld    %d is thinking\n", time, p_num);
	else
	{
		if (!(philo->table->n_lunch) || philo->table->n_lunch != philo->n_eats)
		{
			printf("\033[31m%ld    %d died\n", time, p_num);
			philo->table->some_die = 1;
		}
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
		print_aux(philo, time, philo->p_num + 1, action);
	}
	pthread_mutex_unlock(&philo->table->print);
}
