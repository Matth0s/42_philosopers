/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 08:56:41 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/21 22:37:41 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_actions(philo, 'f');
	pthread_mutex_lock(philo->right_fork);
	print_actions(philo, 'f');
}

void	philo_eat(t_philo *philo)
{
	print_actions(philo, 'e');
	philo->last_eat = m_time();
	m_sleep(philo->table->time_e);
	philo->n_eats++;
	if (philo->table->n_lunch && philo->n_eats == philo->table->n_lunch)
		philo->n_eats = -1;
}

void	philo_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
