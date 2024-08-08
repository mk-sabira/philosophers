/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:21:51 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/08 16:38:42 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_table *table;
    int i;
    long    time_last_meal;
    long die_time_in_microseconds;

    table = (t_table *) arg;
    die_time_in_microseconds = table->die; 
    while (!table->end_simulation)
    {
        i = 0;
        while (i < table->nb_philo)
        {
            time_last_meal = get_current_time() - table->philo[i].last_meal;
            printf("Philo %ld - Last Meal: %ld,Time Last Meal: %ld, Die Time: %ld\n",
                   table->philo[i].id,
                   table->philo[i].last_meal,
                   time_last_meal,
                   die_time_in_microseconds);
            if (time_last_meal > table->die)
            {
                print_info(table, table->philo[i].id, "has died💥", RED);
                printf("if :%ld\n", time_last_meal);
                table->end_simulation = true;
                break;
            }
            i++;
        }
        usleep (1000);
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