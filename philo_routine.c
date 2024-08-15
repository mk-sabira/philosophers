/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:47:28 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/15 15:00:37 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_current_time(void)
{
    struct  timeval time;
    long    milli_sec;

    gettimeofday(&time, NULL);
    milli_sec = (time.tv_sec * 1000) + (time.tv_usec / 1000); 
    return (milli_sec);
}

void print_status(t_table *table, int id, char *mess, char *color)
{
    long timestamp;
    pthread_mutex_lock(&table->start_simul_mutex);
    timestamp = get_current_time() - table->start_simulation;
    pthread_mutex_unlock(&table->start_simul_mutex);
    printf("%s%ld %d %s%s\n", color, timestamp, id, mess, RESET);
}

void    lock_chopsticks(t_philo *philo)
{
    pthread_mutex_lock(&philo->l_chopstick->chopstick);
    pthread_mutex_lock(&philo->r_chopstick->chopstick);
}

void    unlock_chopsticks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->l_chopstick->chopstick);
    pthread_mutex_unlock(&philo->r_chopstick->chopstick);
}

void print_event(t_table *table, int id, char *mess, char *color)
{
	if (!get_end_simulation(table))
        print_status(table, id, mess, color);
}

// bool check_while_eating(table *table)
// {
//     if (table->die < table->eat)
//     {
//         //check
//     }
//     return ()
// }
void    ft_eat(t_table *table, t_philo *philo)
{
    if (get_end_simulation(table))
        return;
    print_event(table, philo->id, "is thinking 🧐", YELLOW);
    lock_chopsticks(philo);

    print_event(table, philo->id, "has taken a left chopstick", BLUE);
    print_event(table, philo->id, "has taken a right chopstick", BLUE);
    if (!get_end_simulation(table))
    {
        lock_eating_mutex(philo, true);
        print_event(table, philo->id, "has started eating🥢", GREEN);
        update_last_meal(philo, get_current_time ());
        /// check here
        usleep(table->eat * 1000);
        
        ///
        unlock_eating_mutex(philo, false);
        
        pthread_mutex_lock(&philo->meal_count_mutex);
        philo->meal_count++;
        pthread_mutex_unlock(&philo->meal_count_mutex);
    }
    if (!get_end_simulation(table))
    {
        print_event(table, philo->id, "put down the left chopstick", BLUE);
        print_event(table, philo->id, "put down the right chopstick", BLUE);
    }
    
    unlock_chopsticks(philo);
}


void    ft_sleep(t_table *table, t_philo *philo)
{
    if (get_end_simulation(table))
        return;
    if (!get_end_simulation(table))
    {
        print_event(table, philo->id, "is sleeping 😴", PURPLE);
        usleep(table->sleep * 1000);
    }
}

bool all_full(t_philo *philo, t_table *table)
{
    int i = 0;
    bool full = true;

    while ((i < table->nb_philo))
    {
        pthread_mutex_lock(&philo[i].meal_count_mutex);
        if (philo[i].meal_count < table->nb_meal)
            full = false;
        pthread_mutex_unlock(&philo[i].meal_count_mutex);
        if (!full)
            return false;
        i++;
    }
    return true;
}

void *philo_routine(void *arg)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *) arg;
    table = philo->table;
    // if (philo->id % 2 == 0)
    //     usleep(table->eat / 2);
    while (!get_end_simulation(table))
    {
        ft_eat(table, philo);
        if (!get_end_simulation(table))
            ft_sleep(table, philo);  
        if ((table->nb_meal != -1) && all_full(table->philo, table)) 
        {
            printf("Philosopher %ld has eaten %ld times.\n", philo->id, philo->meal_count);
            set_end_simulation(table, true); 
        }
    }
    return (NULL);
}
