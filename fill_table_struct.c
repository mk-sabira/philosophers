/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_table_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:26:50 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/20 13:55:26 by bmakhama         ###   ########.fr       */
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
    if (pthread_mutex_init(&table->end_simul_mutex, NULL) != 0)
    {
        free(table);
        error_mess("Error creating end_mutex");
    }
    return (table);
}

t_table	*fill_table_struct(char **arv, t_table	*table)
{
    int i;

	i = 0;
	table = init_table();
    table->nb_philo = ft_atoi(arv[1]);
	if (ft_atoi(arv[2]) < 60 || ft_atoi(arv[3]) < 60 || ft_atoi(arv[4]) < 60)
        print_free(table);
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
