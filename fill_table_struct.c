/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_table_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:26:50 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/21 12:35:24 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(void)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		error_mess("Error allocating table");
	table->nb_philo = 0;
	table->die = 0;
	table->eat = 0;
	table->sleep = 0;
	table->nb_meal = 0;
	table->start_simulation = 0;
	table->end_simulation = false;
	table->chopstick = NULL;
	table->philo = NULL;
	if (pthread_mutex_init(&table->end_simul_mutex, NULL) != 0)
	{
		free(table);
		error_mess("Error creating end_mutex");
	}
	return (table);
}

t_chopstick	*init_chopstick(int nb_philo)
{
	int			i;
	t_chopstick	*chopstick;

	chopstick = malloc(nb_philo * sizeof(t_chopstick));
	if (!chopstick)
		error_mess("Error in allocation");
	i = 0;
	while (i < nb_philo)
	{
		chopstick[i].chop_id = i;
		if (pthread_mutex_init (&chopstick[i].chopstick, NULL) != 0)
			error_mess("error in init mutex");
		i++;
	}
	return (chopstick);
}

void	create_mutexes(t_philo *philos, int i)
{
	if (pthread_mutex_init(&philos[i].last_meal_mutex, NULL) != 0)
	{
		while (i > 1)
			pthread_mutex_destroy(&philos[--i].last_meal_mutex);
		free(philos);
		error_mess("Error creating last_meal_mutex");
	}
	if (pthread_mutex_init(&philos[i].meal_count_mutex, NULL) != 0)
	{
		while (i >= 1)
		{
			pthread_mutex_destroy(&philos[i].last_meal_mutex);
			pthread_mutex_destroy(&philos[i].meal_count_mutex);
			i--;
		}
		free(philos);
		error_mess("Error creating meal_count_mutex");
	}
	if (pthread_mutex_init(&philos[i].eating_mutex, NULL) != 0)
	{
		destroy_mutexes(philos, i);
		free(philos);
		error_mess("Error creating eating_mutex");
	}
}

t_philo	*init_philos(t_table *table)
{
	int		i;
	t_philo	*philos;

	philos = malloc (table->nb_philo * sizeof (t_philo));
	if (!philos)
		error_mess("Error in init philos");
	i = 0;
	while (i < table->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].meal_count = 0;
		philos[i].full = false;
		philos[i].last_meal = 0;
		philos[i].eating = false;
		philos[i].l_chopstick = &table->chopstick[i];
		philos[i].r_chopstick = &table->chopstick[(i + 1) % table->nb_philo];
		philos[i].table = table;
		create_mutexes(philos, i);
		i++;
	}
	return (philos);
}

t_table	*fill_table_struct(char **arv, t_table	*table)
{
	table->nb_philo = ft_atoi(arv[1]);
	if (ft_atoi(arv[1]) == 0 || ft_atoi(arv[2]) < 60 || \
		ft_atoi(arv[3]) < 60 || ft_atoi(arv[4]) < 60)
	{
		pthread_mutex_destroy(&table->end_simul_mutex);
		printf("Can not be less than 60 or equal 0\n");
		free(table);
		exit (1);
	}
	table->die = ft_atoi(arv[2]);
	table->eat = ft_atoi(arv[3]);
	table->sleep = ft_atoi(arv[4]);
	if (arv[5])
		table->nb_meal = ft_atoi(arv[5]);
	else
		table->nb_meal = -1;
	table->chopstick = init_chopstick(table->nb_philo);
	table->philo = init_philos(table);
	return (table);
}
