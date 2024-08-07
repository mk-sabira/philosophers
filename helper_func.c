/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:40:09 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/07 15:30:29 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_mess(char *str)
{
	printf (RED"%s\n", str);
	exit (EXIT_FAILURE);
}
// void    cancel_threads(t_table *table)
// {
// 	int i;

// 	i = 0;
// 	while (i < table->nb_philo)
// 	{
// 		pthread_cancel(table->philo[i].thread_id);
// 		i++;
// 	}
// 	free(table->philo);
// }

// void    destroy_mutex(t_table *table)
// {
// 	int i;

// 	i = 0;
// 	while (i < table->nb_philo)
// 	{
// 		pthread_mutex_destroy(table->chopstick[i].chopstick);
// 		i++;
// 	}
// 	free(table->chopstick);
// }