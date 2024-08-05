/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:28:03 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/05 12:52:45 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		printf("Philo %d is thinking\n", philo->id);
		pthread_mutex_lock(philo->l_chopstick);
		pthread_mutex_lock(philo->r_chopstick);
		printf("Philo %d is eating\n", philo->id);
		pthread_mutex_unlock(philo->r_chopstick);
		pthread_mutex_unlock(philo->l_chopstick);
		printf("Philo %d is sleeping\n", philo->id);
	}
	return (NULL);
}

void	create_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < (*data).nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine, \
			(void *)&philo[i]) != 0)
		{
			printf("Error creating thread for philosopher %d\n", philo[i].id);
			perror("pthread_create");
			exit(1);
		}
	}
}

void	join_philos(t_philo *philos, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	free_mutex(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(philo[i].l_chopstick);
		pthread_mutex_destroy(philo[i].r_chopstick);
		free(philo[i].l_chopstick);
		free(philo[i].r_chopstick);
		i++;
	}
	free(philo);
}
void	fill_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(data->nb_philo * sizeof(t_philo));
	if (!philo)
	{
		printf ("Error philo\n");
		exit (1);
	}
	while (i <= data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].l_chopstick = malloc(sizeof(pthread_mutex_t));
		philo[i].r_chopstick = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].l_chopstick || !philo[i].r_chopstick)
		{
			printf("Error chopstick alloc\n");
			exit(1);
		}
		pthread_mutex_init(philo[i].l_chopstick, NULL);
		pthread_mutex_init(philo[i].r_chopstick, NULL);
		i++;
	}
	create_philos(data, philo);
	join_philos(philo, data->nb_philo);
	free_mutex(data, philo);
}
