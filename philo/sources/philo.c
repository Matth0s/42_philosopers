/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:40:57 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/15 11:15:06 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_parameters(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 4 || argc > 5)
		return (1);
	i = -1;
	while (*(argv + ++i))
	{
		j = -1;
		while (*(*(argv + i) + ++j))
			if (*(*(argv + i) + j) < '0' || *(*(argv + i) + j) > '9')
				return (2);
		if (str_to_long(*(argv + i)) == 0)
			return (3);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (check_parameters(argc - 1, argv + 1))
		return (1);
	if (init_components(argc - 1, argv + 1, &table))
		return (2);
	if (start_simulation(&table))
		printf("Thread Error");
	destroy_components(&table, 1);
	return (0);
}
