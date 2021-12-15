/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:45:18 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/15 08:20:54 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	print_actions(t_philo *philo, char action)
{
	pthread_mutex_lock(&philo->table->print);
	if (action == 'f')
		printf("%ld: %d has taken a fork\n", m_time() - philo->start, philo->p_num + 1);
	else if (action == 'e')
		printf("%ld: %d is eating\n", m_time() - philo->start, philo->p_num + 1);
	else if (action == 's')
		printf("%ld: %d is sleeping\n", m_time() - philo->start, philo->p_num + 1);
	else
		printf("%ld: %d is thinking\n", m_time() - philo->start, philo->p_num + 1);
	pthread_mutex_unlock(&philo->table->print);
}
void	philo_eat(t_philo *philo)
{
	print_actions(philo, 'e');
	m_sleep(philo->table->time_e);
	philo->n_eats++;
}

void	philo_sleep(t_philo *philo)
{
	print_actions(philo, 's');
	m_sleep(philo->table->time_s);
}

void	philo_think(t_philo *philo)
{
	print_actions(philo, 't');
}


void	*simulation(void *arg)
{
	t_philo		*philo;

	philo = (t_philo*)arg;
	while(!(philo->table->begin))
		usleep(1);
	if (philo->p_num % 2 == 1)
		usleep(1);
	philo->start = m_time();
	while (42)
	{
		//philo_forks(philo);
		
		philo_eat(philo);

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


/* void* routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	if (philo->p_num % 2 == 1)
		usleep(0);
	pthread_mutex_lock(philo->forks + philo->p_num);


	printf("o filosofo %d pegou o garfo %p\n", philo->p_num, philo->forks + philo->p_num);
 	if (philo->p_num == philo->n_phis - 1)
	{
		pthread_mutex_lock(philo->forks);
		printf("o filosofo %d pegou o garfo %p\n", philo->p_num, philo->forks);
	}
	else
	{
		pthread_mutex_lock(philo->forks + philo->p_num + 1);
		printf("o filosofo %d pegou o garfo %p\n", philo->p_num,philo->forks + philo->p_num + 1);
	}
	printf("--o filosofo %d ta comendo--\n", philo->p_num );


	pthread_mutex_unlock(philo->forks + philo->p_num);
	printf("o filosofo %d soltou o garfo %p\n", philo->p_num,philo->forks + philo->p_num);
	if (philo->p_num == philo->n_phis - 1)
	{
		pthread_mutex_unlock(philo->forks);
		printf("o filosofo %d soltou o garfo %p\n\n", philo->p_num,philo->forks);
	}
	else
	{
		pthread_mutex_unlock(philo->forks + philo->p_num + 1);
		printf("o filosofo %d soltou o garfo %p\n\n", philo->p_num,philo->forks + philo->p_num + 1);
	}
	return (NULL);
} */
