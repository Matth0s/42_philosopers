/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_components.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:17:48 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/21 23:09:18 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_thread(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->n_phils)
	{
		philo = table->phils + i;
		philo->last_eat = 0;
		philo->n_eats = 0;
		philo->p_num = i + 1;
		philo->left_fork = table->forks + i;
		philo->right_fork = table->forks + i + 1;
		philo->table = table;
	}
	philo->right_fork = table->forks;
}

static int	init_mallocs(t_table *table)
{
	int	i;

	table->forks = NULL;
	table->phils = malloc(table->n_phils * sizeof(t_philo));
	if (!(table->phils))
		return (1);
	table->forks = malloc(table->n_phils * sizeof(pthread_mutex_t));
	if (!(table->forks))
		return (1);
	i = -1;
	while (++i < table->n_phils)
		pthread_mutex_init(table->forks + i, NULL);
	return (0);
}

static void	init_parameters(int argc, char **argv, t_table *table)
{
	table->n_phils = str_to_long(*argv);
	table->time_d = str_to_long(*(argv + 1));
	table->time_e = str_to_long(*(argv + 2));
	table->time_s = str_to_long(*(argv + 3));
	if (argc == 5)
		table->n_lunch = str_to_long(*(argv + 4));
	else
		table->n_lunch = 0;
	table->some_die = 0;
	table->start = 0;
	pthread_mutex_init(&table->print, NULL);
}

int	init_components(int argc, char **argv, t_table *table)
{
	init_parameters(argc, argv, table);
	if (init_mallocs(table))
	{
		destroy_components(table, 0);
		return (1);
	}
	init_thread(table);
	return (0);
}
