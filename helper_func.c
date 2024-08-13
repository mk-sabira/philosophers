/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:40:09 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/13 11:39:09 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_mess(char *str)
{
	printf (RED"%s\n", str);
	exit (EXIT_FAILURE);
}

void    destroy_mutex(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->chopstick[i].chopstick);
		i++;
	}
	free(table->chopstick);
	free(table->philo);
	free(table);
}

void	check_memory(t_table *table)
{
	printf ("can not be less than 60ms\n");
	free(table);
	exit (1);
}

void    destroy_end_mutex(t_table *table)
{
	pthread_mutex_destroy(&table->end_simul_mutex);
}
