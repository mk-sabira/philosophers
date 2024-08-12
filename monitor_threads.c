/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:21:51 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/12 12:37:15 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_table *table;
    int i;
    long    time_last_meal;

    table = (t_table *) arg;
    while (!table->end_simulation)
    {
        i = 0;
        while (i < table->nb_philo)
        {
            time_last_meal = get_current_time() - table->philo[i].last_meal;
            if (time_last_meal > table->die)
            {
                print_info(table, table->philo[i].id, "has died💥", RED, table->philo->meal_count, table->philo->l_chopstick->chop_id, table->philo->r_chopstick->chop_id);
                printf("died at: %ld\n", time_last_meal);
                printf("die time: %ld\n", table->die);
                printf("last meal time: %ld\n", (get_current_time() - table->philo[i].last_meal));
                table->end_simulation = true;
                break;
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