/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:45:18 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/15 09:03:21 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	print_actions(t_philo *philo, char *action)
{
	long int	time;
	int			philosoper;

	time = m_time() - philo->start;
	philosoper = philo->p_num + 1;
	pthread_mutex_lock(&philo->table->print);
	if (*action == 'f' && *(action + 1) == 'l')
		printf("%ld: %d has taken a fork\n", time, philosoper);
	else if (*action == 'f' && *(action + 1) == 'r')
		printf("%ld: %d has taken a fork\n", time, philosoper);
	else if (*action == 'e')
		printf("%ld: %d is eating\n", time, philosoper);
	else if (*action == 's')
		printf("%ld: %d is sleeping\n", time, philosoper);
	else
		printf("%ld: %d is thinking\n", time, philosoper);
	pthread_mutex_unlock(&philo->table->print);
}

void	*simulation(void *arg)
{
	t_philo		*philo;

	philo = (t_philo*)arg;
	while(!(philo->table->begin))
		usleep(1);
	if (philo->p_num % 2 == 1)
		usleep(1000);
	philo->start = m_time();
	while (42)
	{
		philo_take_forks(philo);

		philo_eat(philo);

		philo_drop_forks(philo);

		philo_sleep(philo);

		philo_think(philo);
		if (philo->table->n_lunch)
			if (philo->n_eats == philo->table->n_lunch)
				break;
	}
	return (NULL);
}


int	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_phis)
		if (pthread_create(&(table->phis + i)->pth, NULL, &simulation, table->phis + i))
			return (1);
	table->begin = 1;
	i = -1;
	while (++i < table->n_phis)
		if (pthread_join((table->phis + i)->pth, NULL))
			return (2);
	return (0);
}
