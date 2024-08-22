/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:47:28 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/21 12:51:20 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_table *table, long value)
{
	long wake_up_time;
	
	wake_up_time = get_current_time() + value;
	while (get_current_time() < wake_up_time)
	{
		if (get_end_simulation(table))
			break;
		usleep (500);
	}
}
void	ft_eat(t_table *table, t_philo *philo)
{
	if (get_end_simulation(table))
		return ;
	lock_chopsticks(philo);
	print_event(table, philo->id, "has taken a left chopstick", BLUE);
	print_event(table, philo->id, "has taken a right chopstick", BLUE);
	if (get_end_simulation(table))
	{
		unlock_chopsticks(philo);
		return ;
	}
	print_event(table, philo->id, "has started eating🥢", GREEN);
	lock_eating_mutex(philo, true);
	// usleep(table->eat * 1000);
    ft_usleep(table, table->eat);
	update_last_meal(philo, get_current_time ());
	unlock_eating_mutex(philo, false);
	pthread_mutex_lock(&philo->meal_count_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_count_mutex);
	print_event(table, philo->id, "put down the left chopstick", BLUE);
	print_event(table, philo->id, "put down the right chopstick", BLUE);
	unlock_chopsticks(philo);
}

void	ft_sleep(t_table *table, t_philo *philo)
{
	if (get_end_simulation(table))
		return ;
	if (!get_end_simulation(table))
	{
		print_event(table, philo->id, "is sleeping 😴", PURPLE);
		// usleep(table->sleep * 1000);
		ft_usleep(table, table->sleep);
	}
}

bool	all_full(t_philo *philo, t_table *table)
{
	int		i;
	bool	full;

	i = 0;
	full = true;
	while ((i < table->nb_philo))
	{
		pthread_mutex_lock(&philo[i].meal_count_mutex);
		if (philo[i].meal_count < table->nb_meal)
			full = false;
		pthread_mutex_unlock(&philo[i].meal_count_mutex);
		if (!full)
			return (false);
		i++;
	}
	return (true);
}

void	ft_one_philo(t_table *table)
{
	long	last_meal;

	last_meal = 0;
	pthread_mutex_lock(&table->philo->l_chopstick->chopstick);
	print_event(table, table->philo->id, "has taken a left chopstick", BLUE);
	while (!get_end_simulation(table))
	{
		pthread_mutex_lock(&table->philo->last_meal_mutex);
		last_meal = get_current_time() - table->philo->last_meal;
		pthread_mutex_unlock(&table->philo->last_meal_mutex);		
		if (last_meal > table->die)
		{
			pthread_mutex_unlock(&table->philo->l_chopstick->chopstick);
			set_end_simulation(table, true);
			break ;
		}
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *) arg;
	table = philo->table;
	if (table->nb_philo == 1)
		ft_one_philo(table);
	while (!get_end_simulation(table))
	{
		print_event(table, philo->id, "is thinking 🧐", YELLOW);
		if (!get_end_simulation(table))
			ft_eat(table, philo);
		if (!get_end_simulation(table))
			ft_sleep(table, philo);
		if ((table->nb_meal != -1) && all_full(table->philo, table))
		{
			printf("philo %d ate %ld times.\n", philo->id, philo->meal_count);
			set_end_simulation(table, true);
		}
	}
	return (NULL);
}
