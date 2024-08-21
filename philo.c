/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:05:26 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/21 10:57:38 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philo[i].thread_id, NULL, philo_routine, \
			(void *)&table->philo[i]) != 0)
		{
			destroy_mutexes(table->philo, table->nb_philo);
			free(table->philo);
			if (table->chopstick)
			{
				i = 0;
				while (i < table->nb_philo)
					pthread_mutex_destroy(&table->chopstick[i++].chopstick);
				free(table->chopstick);
			}
			free(table);
			error_mess("Error creating threads");
		}
		i++;
	}
}

void	main_monitor(t_table *table)
{
	int		i;
	long	last_meal;

	while (!get_end_simulation(table))
	{
		i = 0;
		while (i < table->nb_philo)
		{
			pthread_mutex_lock(&table->philo[i].last_meal_mutex);
			last_meal = get_current_time() - table->philo[i].last_meal;
			pthread_mutex_unlock(&table->philo[i].last_meal_mutex);
			pthread_mutex_lock(&table->philo[i].eating_mutex);
			if (!(table->philo[i].eating) && (last_meal > table->die))
			{
				pthread_mutex_unlock(&table->philo[i].eating_mutex);
				set_end_simulation(table, true);
				print_status(table, table->philo[i].id, "has died💥", RED);
				printf("died at: %ld\n", last_meal);
				break ;
			}
			pthread_mutex_unlock(&table->philo[i].eating_mutex);
			i++;
		}
	}
}

int	main(int arc, char **arv)
{
	t_table	*table;
	int		i;

	i = 0;
	if (arc != 5 && arc != 6)
	{
		error_mess("Input should be [5 200 200 300] or [5 200 200 300 [5]]");
		return (1);
	}
	table = parsing_arv(arc, arv);
	table->start_simulation = get_current_time();
	while (i < table->nb_philo)
		table->philo[i++].last_meal = get_current_time();
	create_threads(table);
	main_monitor(table);
	join_child_threads(table);
	clean_table(table);
	return (0);
}
