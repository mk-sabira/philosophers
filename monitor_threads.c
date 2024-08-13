/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:21:51 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/13 14:21:04 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_table *table;
    int i;
    long    time_last_meal;

    table = (t_table *) arg;
    while (!get_end_simulation(table))
    {
        i = 0;
        while (i < table->nb_philo)
        {
            pthread_mutex_lock(&table->philo[i].last_meal_mutex);
            time_last_meal = get_current_time() - table->philo[i].last_meal;
            pthread_mutex_unlock(&table->philo[i].last_meal_mutex);
            if (time_last_meal > table->die)
            {
                set_end_simulation(table, true);
                print_status(table, table->philo[i].id, "has died💥", RED);
                printf("died at: %ld\n", time_last_meal);
                break ;
            }
            i++;
        }
    }
    return (NULL);
}

void monitor_threads(t_table *table)
{
    pthread_t monitor;
    int i;

    pthread_create(&monitor, NULL, monitor_routine, (void *)table);
    i = 0;
    while (i < table->nb_philo)
    {
        pthread_join(table->philo[i].thread_id, NULL);
        i++;
    }
    pthread_join(monitor, NULL);
    destroy_mutex(table);
}