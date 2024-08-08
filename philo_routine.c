/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:47:28 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/08 16:01:33 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_current_time(void)
{
    struct  timeval time;
    long    micro_sec;

    gettimeofday(&time, NULL);
    micro_sec = (time.tv_sec * 1e6) + time.tv_usec;
    return (micro_sec);
}

void print_info(t_table *table, int id, char *mess, char *color )
{
    long    timestamp;

    timestamp = get_current_time() - table->start_simulation;
    printf("%s[%ld] philo %d %s%s\n", color, timestamp / 1000, id, mess, RED);
}

void *philo_routine(void *arg)

{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *) arg;
    table = philo->table;

    while (!table->start_simulation)
        usleep(100);
    philo->last_meal = get_current_time();
    printf("Philo %ld starts with Last Meal Time: %ld\n", philo->id, philo->last_meal);

    while (!table->end_simulation)
    {
        print_info(table, philo->id, "is thinking 🧐", YELLOW);
        
        pthread_mutex_lock(&philo->l_chopstick->chopstick);
        print_info(table, philo->id, "has taken a left chopstick", BLUE);
        pthread_mutex_lock(&philo->r_chopstick->chopstick);
        print_info(table, philo->id, "has taken a right chopstick", BLUE);
        
        print_info(table, philo->id, "has started eating🥢", GREEN);
        philo->last_meal = get_current_time();
        usleep(table->eat);
        philo->meal_count++;
        
        pthread_mutex_unlock(&philo->l_chopstick->chopstick);
        print_info(table, philo->id, "put down the left chopstick", BLUE);
        pthread_mutex_unlock(&philo->r_chopstick->chopstick);
        print_info(table, philo->id, "put down the right chopstick", BLUE);
        
        print_info(table, philo->id, "is sleeping 😴", PURPLE);
        usleep(table->sleep);
        if (table->nb_meal != -1 && philo->meal_count >= table->nb_meal)
        {
            philo->full = true;
        }
    }
    return (NULL);
}
