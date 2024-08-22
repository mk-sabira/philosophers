/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:49:42 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/21 11:50:40 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_table *table, int id, char *mess, char *color)
{
	long	timestamp;

	timestamp = get_current_time() - table->start_simulation;
	pthread_mutex_lock(&table->print_mutex);
	printf("%s%ld %d %s%s\n", color, timestamp, id, mess, RESET);
	pthread_mutex_unlock(&table->print_mutex);
}

void	print_event(t_table *table, int id, char *mess, char *color)
{
	if (!get_end_simulation(table))
		print_status(table, id, mess, color);
}

void	lock_chopsticks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_chopstick->chopstick);
		pthread_mutex_lock(&philo->l_chopstick->chopstick);
	}
	else
	{
		pthread_mutex_lock(&philo->l_chopstick->chopstick);
		pthread_mutex_lock(&philo->r_chopstick->chopstick);
	}
}

void	unlock_chopsticks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->r_chopstick->chopstick);
	pthread_mutex_unlock(&philo->l_chopstick->chopstick);
}
