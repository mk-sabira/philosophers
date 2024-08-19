/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:21:51 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/19 18:55:37 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool all_philo_alive(t_table *table)
{
    int i;

    if (get_end_simulation(table))
        return (false);
    i = 0;
    while (i < table->nb_philo)
    {
        if (get_end_simulation(table))
            return (false);
    
        pthread_mutex_lock(&table->philo[i].last_meal_mutex);
        if (get_end_simulation(table))
        {
            pthread_mutex_unlock(&table->philo[i].last_meal_mutex);
            return (false);
        }
        long last_meal = get_current_time() - table->philo[i].last_meal;
        if (get_end_simulation(table))
        {
            pthread_mutex_unlock(&table->philo[i].last_meal_mutex);
            return (false);
        }
        pthread_mutex_unlock(&table->philo[i].last_meal_mutex);
        
        if (get_end_simulation(table))
        {
            return (false);
        }
        if (last_meal > table->die)
        {
            if (get_end_simulation(table))
                return (false);
            print_status(table, table->philo[i].id, "starvation", RED);
            set_end_simulation(table, true);
            return false;
        }
        i++;
        if (get_end_simulation(table))
            return (false);
    }
    return true;
}

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
            
            pthread_mutex_lock(&table->philo[i].eating_mutex);
            if (!(table->philo[i].eating) && (time_last_meal > table->die))
            {
                pthread_mutex_unlock(&table->philo[i].eating_mutex);
                
                set_end_simulation(table, true);
                print_status(table, table->philo[i].id, "has died💥", RED);
                printf("died at: %ld\n", time_last_meal);
                break ;
            }
            pthread_mutex_unlock(&table->philo[i].eating_mutex);
            i++;
        }
        if (get_end_simulation(table))
            break;
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
