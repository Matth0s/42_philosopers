/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_components.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 01:53:53 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/15 13:56:19 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

static void	init_thread(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->n_phis)
	{
		philo = table->phis + i;
		philo->last_eat = 0;
		philo->n_eats = 0;
		philo->start = 0;
		philo->p_num = i;
		philo->table = table;
	}
}

static int	init_mallocs(t_table *table)
{
	int	i;

	table->forks = NULL;
	table->phis = malloc(table->n_phis * sizeof(t_philo));
	if (!(table->phis))
		return (1);
	table->forks = malloc(table->n_phis * sizeof(pthread_mutex_t));
	if (!(table->forks))
		return (1);
	i = -1;
	while (++i < table->n_phis)
		pthread_mutex_init(table->forks + i, NULL);
	return (0);
}

static void	init_parameters(int argc, char **argv, t_table *table)
{
	table->n_phis = str_to_long(*argv);
	table->time_d = str_to_long(*(argv + 1));
	table->time_e = str_to_long(*(argv + 2));
	table->time_s = str_to_long(*(argv + 3));
	table->some_die = 0;
	table->begin = 0;
	if (argc == 5)
		table->n_lunch = str_to_long(*(argv + 4));
	else
		table->n_lunch = 0;
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
