/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:47:28 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/12 12:41:22 by bmakhama         ###   ########.fr       */
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

pthread_mutex_t table_mutex;
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
    ft_lock_philo(philo);
    print_info(table, philo->id, "is thinking 🧐", YELLOW, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
    print_info(table, philo->id, "has taken a left chopstick", BLUE, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
    print_info(table, philo->id, "has taken a right chopstick", BLUE, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
    print_info(table, philo->id, "has started eating🥢", GREEN, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
    usleep(table->eat);
    philo->meal_count++;
    philo->last_meal = get_current_time();
    print_info(table, philo->id, "put down the left chopstick", BLUE, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
    print_info(table, philo->id, "put down the right chopstick", BLUE, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);  
    ft_unlock_philo(philo);
}

void    ft_sleep(t_table *table, t_philo *philo)
{
    ft_lock_philo(philo);
    print_info(table, philo->id, "is sleeping 😴", PURPLE, philo->meal_count, philo->l_chopstick->chop_id, philo->r_chopstick->chop_id);
    usleep(table->sleep);
    ft_unlock_philo(philo);
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
        ft_eat(table, philo);
        ft_sleep(table, philo);
    }
    return (NULL);
}
