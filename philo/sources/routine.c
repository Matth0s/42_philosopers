/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:45:18 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/11 02:46:06 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.c"

/* void* routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	if (philo->p_num % 2 == 1)
		usleep(0);
	pthread_mutex_lock(philo->forks + philo->p_num);


	printf("o filosofo %d pegou o garfo %p\n", philo->p_num, philo->forks + philo->p_num);
 	if (philo->p_num == philo->n_phis - 1)
	{
		pthread_mutex_lock(philo->forks);
		printf("o filosofo %d pegou o garfo %p\n", philo->p_num, philo->forks);
	}
	else
	{
		pthread_mutex_lock(philo->forks + philo->p_num + 1);
		printf("o filosofo %d pegou o garfo %p\n", philo->p_num,philo->forks + philo->p_num + 1);
	}
	printf("--o filosofo %d ta comendo--\n", philo->p_num );


	pthread_mutex_unlock(philo->forks + philo->p_num);
	printf("o filosofo %d soltou o garfo %p\n", philo->p_num,philo->forks + philo->p_num);
	if (philo->p_num == philo->n_phis - 1)
	{
		pthread_mutex_unlock(philo->forks);
		printf("o filosofo %d soltou o garfo %p\n\n", philo->p_num,philo->forks);
	}
	else
	{
		pthread_mutex_unlock(philo->forks + philo->p_num + 1);
		printf("o filosofo %d soltou o garfo %p\n\n", philo->p_num,philo->forks + philo->p_num + 1);
	}
	return (NULL);
}
 */


/* 	i = -1;
	while (++i < table.n_phis)
	{
		if (pthread_create(&(table.phis + i)->pth, NULL, &routine, (table.phis + i)) != 0)
			return (1);
	}

	i = -1;
	while (++i < table.n_phis)
		if (pthread_join((table.phis + i)->pth, NULL) != 0)
			return (2);

	i = -1;
	while (++i < table.n_phis)
		pthread_mutex_init(table.phis->forks + i, NULL); */