/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_components.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 01:51:54 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/16 17:42:23 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_components(t_table *table, int mutex_init)
{
	int	i;

	i = -1;
	if (table->phis)
		free(table->phis);
	table->phis = NULL;
	i = -1;
	if (mutex_init)
		while (++i < table->n_phis)
			pthread_mutex_destroy(table->forks + i);
	pthread_mutex_destroy(&table->print);
	if (table->forks)
		free(table->forks);
	table->forks = NULL;
}
