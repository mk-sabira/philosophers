/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:40:14 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/05 12:25:35 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_data
{
	int	nb_philo;
	int	die;
	int	eat;
	int	sleep;
	int	each_ph;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*l_chopstick;
	pthread_mutex_t	*r_chopstick;
}	t_philo;

//parsing
t_data	*parsing_arv(int arc, char **arv);
t_data	*init_data(void);
t_data	*fill_data(char **arv);

void	fill_philo(t_data *data);
#endif