/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:01:02 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/19 17:43:07 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    destroy_mutexes(t_philo *philos, int i)
{
    int j;

    j = 1;
    while (j < i)
    {
        pthread_mutex_destroy(&philos[j].last_meal_mutex);
        pthread_mutex_destroy(&philos[j].meal_count_mutex);
        pthread_mutex_destroy(&philos[j].eating_mutex);
        j++;
    }
}

void    create_mutexes(t_philo *philos, int i)
{
    if (pthread_mutex_init(&philos[i].last_meal_mutex, NULL) != 0)
    {
        while (i > 1)
            pthread_mutex_destroy(&philos[--i].last_meal_mutex);
            free(philos);
            error_mess("Error creating last_meal_mutex");
    }
    if (pthread_mutex_init(&philos[i].meal_count_mutex, NULL) != 0)
    {
        while (i >= 1)
        {
            pthread_mutex_destroy(&philos[i].last_meal_mutex);
            pthread_mutex_destroy(&philos[i].meal_count_mutex);
            i--;
        }
        free(philos);
        error_mess("Error creating meal_count_mutex");
    }
    if  (pthread_mutex_init(&philos[i].eating_mutex, NULL) != 0)
    {
        destroy_mutexes(philos, i);
        free(philos);
        error_mess("Error creating eating_mutex");
    }
}

t_philo   *init_philos(t_table *table)
{
    int i;
    t_philo *philos;

    philos= malloc (table->nb_philo * sizeof (t_philo));
    if (!philos)
        error_mess("Error in init philos");
    i = 0;
    while (i <= table->nb_philo)
    {
        philos[i].id = i + 1;//philos start from 1 not 0
        philos[i].meal_count = 0;
        philos[i].full = false;
        philos[i].last_meal = 0;
        philos[i].eating = false;
        philos[i].l_chopstick = &table->chopstick[i];
        philos[i].r_chopstick = &table->chopstick[(i + 1) % table->nb_philo];
        philos[i].table = table;
        create_mutexes(philos, i);
        i++;
    }
    return (philos);
}
