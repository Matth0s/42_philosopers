/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:45:18 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/16 17:54:38 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*simulation(void *arg)
{
	t_philo		*philo;
	pthread_t	check_die;

	philo = (t_philo *)arg;
	if (philo->p_num % 2 == 1)
		m_sleep(1);
	philo->last_eat = philo->table->start;
	pthread_create(&check_die, NULL, &philo_die, philo);
	pthread_detach(check_die);
	while (!(philo->table->some_die))
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_drop_forks(philo);
		if (philo->table->n_lunch && philo->n_eats == philo->table->n_lunch)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_phis)
	{
		table->start = m_time();
		if (pthread_create(&(table->phis + i)->pth, NULL, &simulation,
				table->phis + i))
			return (1);
	}
	i = -1;
	while (++i < table->n_phis)
		if (pthread_join((table->phis + i)->pth, NULL))
			return (2);
	if (!(table->some_die))
		printf("full stomach philosophers\n");
	return (0);
}
