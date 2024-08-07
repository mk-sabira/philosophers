/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:47:28 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/07 17:50:41 by bmakhama         ###   ########.fr       */
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

    timestamp = get_current_time();
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
    while(!table->end_simulation)
    {
        print_info(table, philo->id, "is thinking", YELLOW);
        pthread_mutex_lock(&philo->l_chopstick->chopstick);
        print_info(table, philo->id, "has taken a chopstick", BLUE);
        pthread_mutex_lock(&philo->r_chopstick->chopstick);
        print_info(table, philo->id, "has taken a chopstick", BLUE);
    }
}
