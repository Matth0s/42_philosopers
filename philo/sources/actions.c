/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 08:56:41 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/15 14:16:52 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->table->forks + philo->p_num);
	print_actions(philo, "fl");
	if (philo->p_num + 1 == philo->table->n_phis)
	{
		pthread_mutex_lock(philo->table->forks);
		print_actions(philo, "fr");
	}
	else
	{
		pthread_mutex_lock(philo->table->forks + philo->p_num + 1);
		print_actions(philo, "fr");
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	print_actions(philo, "e");
	m_sleep(philo->table->time_e);
	philo->n_eats++;
	pthread_mutex_unlock(&philo->mutex);
}

void	philo_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->table->forks + philo->p_num);
	if (philo->p_num + 1 == philo->table->n_phis)
		pthread_mutex_unlock(philo->table->forks);
	else
		pthread_mutex_unlock(philo->table->forks + philo->p_num + 1);
}

void	philo_sleep(t_philo *philo)
{
	print_actions(philo, "s");
	m_sleep(philo->table->time_s);
}

void	philo_think(t_philo *philo)
{
	print_actions(philo, "t");
}
