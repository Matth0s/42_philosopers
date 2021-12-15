/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:55 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/14 21:44:04 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t		pth;
	long int		die;
	long int		eat;
	long int		sleep;
	long int		start;
	int				n_eats;
	int				p_num;
	t_table			*table;
}					t_philo;

struct s_table
{
	int				n_phis;
	long int		time_d;
	long int		time_e;
	long int		time_s;
	int				n_lunch;
	int				begin;
	t_philo			*phis;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
};

int			init_components(int argc, char **argv, t_table *table);
int			start_simulation(t_table *table);
void		destroy_components(t_table *table, int mutex_init);



long int	str_to_long(char *nptr);
void		m_sleep(long int time);
long int	m_time(void);

#endif
