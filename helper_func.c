/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:40:09 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/23 11:14:11 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_is_even(t_table *table)
{
	if (table->nb_philo > 100)
		usleep(table->eat * 1000);
	else
		usleep(table->nb_philo * 1000);
}

void	join_child_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philo[i].thread_id, NULL);
		i++;
	}
}

void	destroy_mutexes(t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&philo[i].last_meal_mutex);
		pthread_mutex_destroy(&philo[i].meal_count_mutex);
		pthread_mutex_destroy(&philo[i].eating_mutex);
		i++;
	}
}

void	clean_table(t_table *table)
{
	int	i;

	if (table)
	{
		if (table->philo)
		{
			destroy_mutexes(table->philo, table->nb_philo);
			free(table->philo);
		}
		if (table->chopstick)
		{
			i = 0;
			while (i < table->nb_philo)
			{
				pthread_mutex_destroy(&table->chopstick[i].chopstick);
				i++;
			}
			free(table->chopstick);
		}
		pthread_mutex_destroy(&table->end_simul_mutex);
		pthread_mutex_destroy(&table->print_mutex);
		free(table);
	}
}
