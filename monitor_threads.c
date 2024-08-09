/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:21:51 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/09 12:33:43 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_table *table;
    int i;
    long    time_last_meal;
    long die_time_in_microseconds;
    long    current_time;

    table = (t_table *) arg;
    die_time_in_microseconds = table->die; 
    while (!table->end_simulation)
    {
        i = 0;
        while (i < table->nb_philo)
        {
            current_time = get_current_time();
            time_last_meal = current_time - table->philo[i].last_meal;
            // printf("last: %ld\n", table->philo[i].last_meal);
            // printf("Philo %ld - Last Meal: %ld, Time Last Meal: %ld, Current Time: %ld, Die Time: %ld\n",
            //             table->philo[i].id,
            //             table->philo[i].last_meal,
            //             time_last_meal,
            //             current_time,
            //             die_time_in_microseconds);
            if (time_last_meal > table->die)
            {
                print_info(table, table->philo[i].id, "has died💥", RED);
                printf("die time: %ld\n", time_last_meal);
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