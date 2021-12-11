/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:55 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/11 02:50:32 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <pthread.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t		pth;
	long int		die;
	long int		eat;
	long int		sleep;
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
	pthread_mutex_t	*forks;
	t_philo			*phis;
};

long int	str_to_long(char *nptr);
int			init_components(int argc, char **argv, t_table *table);
void		destroy_components(t_table *table, int mutex_init);

#endif
