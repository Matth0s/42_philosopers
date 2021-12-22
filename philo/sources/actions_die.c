/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:48:18 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/21 23:04:17 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	full_tummy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_phils)
		if ((table->phils + i)->n_eats >= 0)
			return (0);
	return (1);
}

static void	some_die(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_phils)
		if ((table->phils + i)->n_eats >= 0)
			if (table->time_d < m_time() - (table->phils + i)->last_eat)
				print_actions(table->phils + i, 'd');
	i = -1;
	if (table->some_die)
		while (++i < table->n_phils)
			pthread_mutex_unlock(table->forks + i);
}

void	*philo_die(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (42)
	{
		if (table->some_die)
			break ;
		if (full_tummy(table))
			break ;
		some_die(table);
	}
	return (NULL);
}
