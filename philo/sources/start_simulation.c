/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:45:18 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/16 12:33:24 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	print_actions(t_philo *philo, char *action)
{
	long int	time;
	int			philosoper;

	time = m_time() - philo->start;
	philosoper = philo->p_num + 1;
	pthread_mutex_lock(&philo->table->print);
	if (!(philo->table->some_die))
	{
		if (*action == 'f' && *(action + 1) == 'l')
			printf(PURPLE"%ld    %d has taken a fork\n"RESET, time, philosoper);
		else if (*action == 'f' && *(action + 1) == 'r')
			printf(MAGENTA"%ld    %d has taken a fork\n"RESET, time, philosoper);
		else if (*action == 'e')
			printf(GREEN"%ld    %d is eating\n"RESET, time, philosoper);
		else if (*action == 's')
			printf(CYAN"%ld    %d is sleeping\n"RESET, time, philosoper);
		else if (*action == 't')
			printf(YELLOW"%ld    %d is thinking\n"RESET, time, philosoper);
		else
		{
			printf(RED"%ld    %d died\n"RESET, time, philosoper);
			philo->table->some_die = philosoper;
		}
	}
	pthread_mutex_unlock(&philo->table->print);
}

void	philo_die(t_philo *philo)
{
	if (philo->table->time_d < m_time() - philo->last_eat)
		print_actions(philo, "die");
}

void	*check_die(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	while (!(philo->table->some_die))
		if (philo->last_eat)
			philo_die(philo);
	return (NULL);
}

void	*simulation(void *arg)
{
	t_philo		*philo;
	pthread_t	die;

	philo = (t_philo *)arg;
	while (!(philo->table->begin))
		usleep(1);
	if (philo->p_num % 2 == 1)
		m_sleep(1);
	pthread_create(&die, NULL, &check_die, philo);
	pthread_detach(die);
	philo->start = m_time();
	while (!(philo->table->some_die))
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_drop_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (philo->table->n_lunch)
			if (philo->n_eats == philo->table->n_lunch)
				break ;
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_phis)
		if (pthread_create(&(table->phis + i)->pth, NULL, &simulation,
				table->phis + i))
			return (1);
	table->begin = 1;
	i = -1;
	while (++i < table->n_phis)
		if (pthread_join((table->phis + i)->pth, NULL))
			return (2);
	return (0);
}
