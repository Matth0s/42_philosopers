/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:08:49 by mmoreira          #+#    #+#             */
/*   Updated: 2021/12/11 02:52:35 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long int	str_to_long(char *nptr)
{
	long int	number;
	int			i;

	i = -1;
	number = 0;
	while (*(nptr + ++i))
		number = (number * 10) + (*(nptr + i) - '0');
	return (number);
}
