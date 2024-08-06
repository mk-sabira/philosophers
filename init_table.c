/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:26:50 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/06 12:53:28 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_philos(t_table *table)
{
    t_chopstick *chopstick;
    int         i;

    chopstick = malloc(sizeof (table->nb_philo * sizeof(t_chopstick)));
    if (!chopstick)
        error_mess("Error in allocation");
    i = 0;
    while (i < table->nb_philo)
    {
        table->chopstick[i].chop_id = i;
        if (pthread_mutex_init (&table->chopstick[i].chopstick, NULL) != 0)
            error_mess("error in init mutex");
        i++;
    }
}
void    init_philos(t_table *table)
{
    int i;

    table->nb_philo = malloc (sizeof(nb_philo));
    if (!table->nb_philo)
        error_mess("Error in init philos");
    i = 0;
    while (i < table->nb_philo)
    {
        table->nb_philo[i].id = i;
        table->die
    }
}
void    init_table(t_table *table)
{
    table->end_simulation = false;
    init_chopstick();
    init_philos();
}