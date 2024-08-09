/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_table_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:26:50 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/09 12:54:42 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_chopstick    *init_chopstick(int nb_philo)
{
    int         i;
    t_chopstick *chopstick;

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
t_philo   *init_philos(t_table *table)
{
    int i;
    t_philo *philos;

    philos= malloc (table->nb_philo * sizeof (t_philo));
    if (!philos)
        error_mess("Error in init philos");
    i = 0;
    while (i < table->nb_philo)
    {
        philos[i].id = i;
        philos[i].meal_count = 0;
        philos[i].full = false;
        philos[i].last_meal = 0;
        philos[i].l_chopstick = &table->chopstick[i];
        philos[i].r_chopstick = &table->chopstick[(i + 1) % table->nb_philo];
        philos[i].table = table;
        if (pthread_create(&philos[i].thread_id, NULL, philo_routine, (void *)&philos[i]) != 0)
            error_mess("Error creating threads");
        i++;
    }
    return (philos);
}
t_table    *init_table(void)
{
    t_table *table;

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
    return (table);
}
t_table	*fill_table_struct(char **arv, t_table	*table)
{
	table = init_table();
    int i = 0;
	
    table->nb_philo = ft_atoi(arv[1]);
	if (ft_atoi(arv[2]) < 60 || ft_atoi(arv[3]) < 60 || ft_atoi(arv[4]) < 60)
	{
		printf ("can not be less than 60ms\n");
		free(table);
		exit (1);
	}
	else
	{
		table->die = ft_atoi(arv[2]) * 1e3;
		table->eat = ft_atoi(arv[3]) * 1e3;
		table->sleep = ft_atoi(arv[4]) * 1e3;	
	}
	if (arv[5])
		table->nb_meal = ft_atoi(arv[5]);
	else
		table->nb_meal = -1;
    table->chopstick = init_chopstick(table->nb_philo);
	table->philo = init_philos(table);
    while (i < table->nb_philo)
	{
		table->philo[i].last_meal = get_current_time();
		i++;
	}
	return (table);
}

void print_table(t_table *table)
{
    int i;

    if (!table) {
        printf("Table is NULL\n");
        return;
    }

    printf("Number of Philosophers: %ld\n", table->nb_philo);
    printf("Time to Die: %ld ms\n", table->die);
    printf("Time to Eat: %ld ms\n", table->eat);
    printf("Time to Sleep: %ld ms\n", table->sleep);
    printf("Number of Meals: %ld\n", table->nb_meal);

    // Print chopsticks
    printf("Chopsticks:\n");
    for (i = 0; i < table->nb_philo; i++) {
        printf("Chopstick %d: mutex %p\n", table->chopstick[i].chop_id, (void *)&table->chopstick[i].chopstick);
    }

    // Print philosophers
    printf("Philosophers:\n");
    for (i = 0; i < table->nb_philo; i++) {
        printf("Philosopher %ld: meal_count=%ld, full=%d, last_meal=%ld, left_chopstick=%d, right_chopstick=%d\n",
               table->philo[i].id,
               table->philo[i].meal_count,
               table->philo[i].full,
               table->philo[i].last_meal,
               table->philo[i].l_chopstick->chop_id,
               table->philo[i].r_chopstick->chop_id);
    }
}
