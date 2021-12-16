/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:45:18 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/16 14:23:57 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	print_actions(t_philo *philo, char *action)
{
	long int	time;
	int			p_num;

	pthread_mutex_lock(&philo->table->print);
	if (!(philo->table->some_die))
	{
		time = m_time() - philo->table->start;
		p_num = philo->p_num + 1;
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
			printf(RED"%ld    %d died\n"RESET, time, p_num);
			philo->table->some_die = p_num;
		}
	}
	pthread_mutex_unlock(&philo->table->print);
}

int		philo_die(t_philo *philo)
{
	if (!philo->last_eat)
	{
		if (philo->table->time_d < m_time() - philo->table->start)
		{
			//printf("1  %d  -  %ld  -  %ld  -  %ld  -  %ld\n", philo->p_num + 1, philo->table->time_d, m_time() - philo->table->start, m_time(), philo->table->start );
			print_actions(philo, "die");
			return (1);
		}
	}
	else
	{
		if (philo->table->time_d < m_time() - philo->last_eat)
		{
			//printf("2  %d  -  %ld  -  %ld  -  %ld -  %ld\n", philo->p_num + 1, philo->table->time_d,m_time() - philo->last_eat, m_time(), philo->last_eat );
			print_actions(philo, "die");
			return (1);
		}
	}
	return (0);
}

void	*check_die(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	if (philo->p_num % 2 == 0)
		m_sleep(1);
	while (!(philo_die(philo)))
		continue;
	// while (philo && !(philo->table->some_die))
	// 	continue;
	// 	if (philo->last_eat)
	// 		continue ;
			//philo_die(philo);
	return (NULL);
}

void	*simulation(void *arg)
{
	t_philo		*philo;
	//pthread_t	die;

	philo = (t_philo *)arg;
/* 	while (!(philo->table->begin))
		usleep(1); */
	if (philo->p_num % 2 == 1)
		m_sleep(1);
/* 	pthread_create(&die, NULL, &check_die, philo);
	pthread_detach(die); */
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
	{
		table->start = m_time();
		if (pthread_create(&(table->phis + i)->pth, NULL, &simulation,
				table->phis + i))
			return (1);
	}
/* 	table->begin = 1; */
	i = -1;
	while (++i < table->n_phis)
		if (pthread_join((table->phis + i)->pth, NULL))
			return (2);
	return (0);
}
