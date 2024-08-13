/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_contol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:52:43 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/13 14:05:05 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_end_simulation(t_table *table, bool value)
{
	pthread_mutex_lock(&table->end_simul_mutex);
	table->end_simulation = value;
	pthread_mutex_unlock(&table->end_simul_mutex);
}

bool	get_end_simulation(t_table *table)
{
	bool result;
	pthread_mutex_lock(&table->end_simul_mutex);
	result = table->end_simulation;
	pthread_mutex_unlock(&table->end_simul_mutex);
	return (result);
}

void	update_last_meal(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
}