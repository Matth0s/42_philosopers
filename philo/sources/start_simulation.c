/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:45:18 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/22 16:47:28 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*simulation(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (!(philo->p_num % 2))
		m_sleep(1);
	while (42)
	{
		if (philo->table->some_die)
			break ;
		philo_take_forks(philo);
		philo_eat(philo);
		philo_drop_forks(philo);
		if (philo->n_eats < 0)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	pthread_t	check_die;
	int			i;

	i = -1;
	table->start = m_time();
	while (++i < table->n_phils)
		if (pthread_create(&(table->phils + i)->pth, NULL, &simulation,
				table->phils + i))
			return (1);
	if (pthread_create(&check_die, NULL, &philo_die, table))
		return (1);
	i = -1;
	while (++i < table->n_phils)
		if (pthread_join((table->phils + i)->pth, NULL))
			return (2);
	if (pthread_join(check_die, NULL))
		return (2);
	if (!(table->some_die))
		printf("\nfull stomach philosophers\n");
	return (0);
}
