/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:47:28 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/11 12:47:15 by bmakhama         ###   ########.fr       */
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

void print_info(t_table *table, int id, char *mess, char *color, int meal_count, int l_chopstick_id, int r_chopstick_id)
{
    long timestamp = get_current_time() - table->start_simulation;
    printf("%s[%ld] %d %s nb_meal: %d, l_chopstick: %d, r_chopstick: %d%s\n", color, timestamp / 1000, id, mess, meal_count, \
        l_chopstick_id, r_chopstick_id, RED);
}

int ft_take_chop(t_table *table, t_philo *philo)
{
    if (pthread_mutex_lock(&philo->l_chopstick->chopstick) == 0)
    {
        if (table->end_simulation)
            return (0);
        print_info(table, philo->id, "took chopstick", BLUE, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
        if (pthread_mutex_lock(&philo->r_chopstick->chopstick) == 0)
        {
            if (table->end_simulation)
            {
                pthread_mutex_unlock(&philo->r_chopstick->chopstick);
                return (0);
            }
            return (1);
        }
        pthread_mutex_unlock(&philo->l_chopstick->chopstick);
    }
    return (0);
}

void    ft_eat(t_table *table, t_philo *philo)
{
    print_info(table, philo->id, "has started eating🥢", GREEN, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
    usleep(table->eat);
    philo->meal_count++;
} 

void ft_sleep(t_table *table, t_philo *philo)
{
    pthread_mutex_unlock(&philo->l_chopstick->chopstick);
    print_info(table, philo->id, "put down the left chopstick", BLUE, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
    pthread_mutex_unlock(&philo->r_chopstick->chopstick);
    print_info(table, philo->id, "put down the right chopstick", BLUE, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
    print_info(table, philo->id, "is sleeping 😴", PURPLE, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
    usleep(table->sleep);
}  
void *philo_routine(void *arg)

{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *) arg;
    table = philo->table;
    while (!table->start_simulation);
    while (!table->end_simulation)
    {
        if(!philo->full)
        {
            print_info(table, philo->id, "is thinking 🧐", YELLOW, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
            if (ft_take_chop(table, philo))
            {
                if (!table->end_simulation)
                {
                    ft_eat(table, philo);
                    philo->last_meal = get_current_time();
                }
                pthread_mutex_unlock(&philo->l_chopstick->chopstick);
                pthread_mutex_unlock(&philo->r_chopstick->chopstick);
            }
        }
        if (!table->end_simulation || philo->full)
            ft_sleep(table, philo);
        if (table->nb_meal != -1 && philo->meal_count >= table->nb_meal)
            philo->full = true;
    }
    pthread_mutex_unlock(&philo->l_chopstick->chopstick);
    pthread_mutex_unlock(&philo->r_chopstick->chopstick);
    return (NULL);
}
