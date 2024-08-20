/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:40:09 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/20 13:54:15 by bmakhama         ###   ########.fr       */
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

	i = 1;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->chopstick[i].chopstick);
		i++;
	}
	free(table->chopstick);
	free(table->philo);
	free(table);
}

void	print_free(t_table *table)
{
	printf ("can not be less than 60ms\n");
	free(table);
	exit (1);
}

void    destroy_end_mutex(t_table *table)
{
	pthread_mutex_destroy(&table->end_simul_mutex);
}
void	join_child_threads(t_table *table)
{
	int i;
	
	i = 0;
	while (i < table->nb_philo)
        pthread_join(table->philo[i++].thread_id, NULL);
}