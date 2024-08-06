/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:28:03 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/06 09:51:58 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define THINK_TIME 1000000  // 1 second
#define EAT_TIME 2000000    // 2 seconds
#define SLEEP_TIME 1000000 

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		printf(YELLOW "Philo %d is thinking 🤔" RESET "\n", philo->id);
		usleep(THINK_TIME);
		pthread_mutex_lock(philo->l_chopstick);
		pthread_mutex_lock(philo->r_chopstick);
		printf(GREEN "Philo %d is eating 🍜" RESET "\n", philo->id);
		usleep(EAT_TIME);
		pthread_mutex_unlock(philo->r_chopstick);
		pthread_mutex_unlock(philo->l_chopstick);
		printf(BLUE "Philo %d is sleeping 😴" RESET "\n", philo->id);
		usleep(SLEEP_TIME);
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
		i++;
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

void	free_mutex(t_data *data, t_philo *philo, pthread_mutex_t *chopsticks)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&chopsticks[i]);
		i++;
	}
	free(chopsticks);
	free(philo);
}

void	fill_philo(t_data *data)
{
	t_philo			*philo;
	pthread_mutex_t	*chopsticks;
	int				i;

	i = 0;
	philo = malloc(data->nb_philo * sizeof(t_philo));
	if (!philo)
	{
		printf ("Error philo\n");
		exit (1);
	}
	chopsticks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if (!chopsticks)
	{
		printf ("Error chopsticks\n");
		free(philo);
		exit (1);
	}
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&chopsticks[i], NULL) != 0)
		{
			printf("Error: Could not initialize mutex\n");
			free(philo);
			free(chopsticks);
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i <= data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].l_chopstick = &chopsticks[i];
		philo[i].r_chopstick = &chopsticks[(i + 1) % data->nb_philo];
		if (!philo[i].l_chopstick || !philo[i].r_chopstick)
		{
			printf("Error chopstick alloc\n");
			exit(1);
		}
		i++;
	}
	create_philos(data, philo);
	join_philos(philo, data->nb_philo);
	free_mutex(data, philo, chopsticks);
}
