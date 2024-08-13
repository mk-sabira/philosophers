/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:47:28 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/13 15:15:28 by bmakhama         ###   ########.fr       */
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

void print_status(t_table *table, int id, char *mess, char *color)
{
    long timestamp;

    pthread_mutex_lock(&table->start_simul_mutex);
    timestamp = get_current_time() - table->start_simulation;
    pthread_mutex_unlock(&table->start_simul_mutex);
    printf("%s%ld %d %s%s\n", color, timestamp / 1000, id, mess, RED);
}

void print_chopstick_info(t_table *table, int id, int meal_count, int l_chopstick_id, int r_chopstick_id)
{
    long timestamp;
    
    timestamp = get_current_time() - table->start_simulation;
    printf("[%ld] %d nb_meal: %d, l_chopstick: %d, r_chopstick: %d\n", timestamp / 1000, id, meal_count, \
        l_chopstick_id, r_chopstick_id);
}

void    ft_lock_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->l_chopstick->chopstick);
    pthread_mutex_lock(&philo->r_chopstick->chopstick);

}

void    ft_unlock_philo(t_philo *philo)
{
    pthread_mutex_unlock(&philo->l_chopstick->chopstick);
    pthread_mutex_unlock(&philo->r_chopstick->chopstick);
}

void    ft_eat(t_table *table, t_philo *philo)
{
    // ft_lock_philo(philo);

    if (!get_end_simulation(table))
        print_status(table, philo->id, "is thinking 🧐", YELLOW);

    if (!get_end_simulation(table))
        print_status(table, philo->id, "has taken a left chopstick", BLUE);

    if (!get_end_simulation(table))
        print_status(table, philo->id, "has taken a right chopstick", BLUE);
    
    
    if (!get_end_simulation(table))
    {
        print_status(table, philo->id, "has started eating🥢", GREEN);
        usleep(table->eat);
        philo->meal_count++;
        update_last_meal(philo, get_current_time ());
        // printf("Philosopher %ld updated last_meal to %ld\n", philo->id,  philo->last_meal); // Debug output
    }
    
    if (!get_end_simulation(table))
        print_status(table, philo->id, "put down the left chopstick", BLUE);
    
    if (!get_end_simulation(table))
        print_status(table, philo->id, "put down the right chopstick", BLUE);
    // ft_unlock_philo(philo);
}


void    ft_sleep(t_table *table, t_philo *philo)
{
    // ft_lock_philo(philo);
    if (!get_end_simulation(table))
    {
        print_status(table, philo->id, "is sleeping 😴", PURPLE);
        usleep(table->sleep);
    }
    // ft_unlock_philo(philo);
}

void *philo_routine(void *arg)
{
    printf("called\n");
    t_philo *philo;
    t_table *table;

    philo = (t_philo *) arg;
    table = philo->table;
    // while (!table->end_simulation);
    while (!get_end_simulation(table))
    {
        if (!get_end_simulation(table))
        {
            ft_eat(table, philo);
        }
        if (!get_end_simulation(table))
            ft_sleep(table, philo);
    }
    return (NULL);
}
