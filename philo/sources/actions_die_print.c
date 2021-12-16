/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_die_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:48:18 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/16 17:12:34 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_aux(t_philo *philo, long int time, int p_num, char *action)
{
	if (*action == 'f' && *(action + 1) == 'l')
		printf(PURPLE"%ld    %d has taken a fork\n"RESET, time, p_num);
	else if (*action == 'f' && *(action + 1) == 'r')
		printf(MAGENTA"%ld    %d has taken a fork\n"RESET, time, p_num);
	else if (*action == 'e')
		printf(GREEN"%ld    %d is eating\n"RESET, time, p_num);
	else if (*action == 's')
		printf(CYAN"%ld    %d is sleeping\n"RESET, time, p_num);
	else if (*action == 't')
		printf(YELLOW"%ld    %d is thinking\n"RESET, time, p_num);
	else
	{
		if (!(philo->table->n_lunch) || philo->table->n_lunch != philo->n_eats)
		{
			printf(RED"%ld    %d died\n"RESET, time, p_num);
			philo->table->some_die = 1;
		}
	}
}

void	print_actions(t_philo *philo, char *action)
{
	long int	time;

	pthread_mutex_lock(&philo->table->print);
	if (!(philo->table->some_die))
	{
		time = m_time() - philo->table->start;
		print_aux(philo, time, philo->p_num + 1, action);
	}
	pthread_mutex_unlock(&philo->table->print);
}

void	*philo_die(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!(philo->table->some_die))
	{
		if (philo->table->n_lunch && philo->n_eats == philo->table->n_lunch)
			break ;
		if (philo->table->time_d < m_time() - philo->last_eat)
			print_actions(philo, "die");
	}
	return (NULL);
}
