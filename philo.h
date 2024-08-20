/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:40:14 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/20 13:56:42 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define WHITE "\033[28m"

typedef struct s_table t_table;

typedef	struct s_chopstick
{
	pthread_mutex_t	chopstick;
	int 			chop_id;
}	t_chopstick;

typedef struct s_philo
{
	long			id;
	long 		meal_count;
	bool		full;
	long		last_meal;
	bool eating;
	t_chopstick *l_chopstick;
	t_chopstick *r_chopstick;
	pthread_t		thread_id;
	t_table		*table;
	pthread_mutex_t last_meal_mutex;
	pthread_mutex_t meal_count_mutex;
	pthread_mutex_t eating_mutex;
}	t_philo;


struct s_table
{
	int		nb_philo;
	long		die;
	long		eat;
	long		sleep;
	long		nb_meal;
	long		start_simulation;
	bool		simulation_started;
	bool		end_simulation;
	pthread_mutex_t end_simul_mutex;
	t_chopstick	*chopstick;
	t_philo 	*philo;
};

//parsing
t_table *parsing_arv(int arc, char **arv);
t_philo   *init_philos(t_table *table);
t_table    *init_table(void);
t_table	*fill_table_struct(char **arv, t_table	*table);
void    *philo_routine(void *arg);
long    get_current_time(void);

//print
void print_status(t_table *table, int id, char *mess, char *color);

//helper functions
long	ft_atoi(const char *str);
void    error_mess(char *str);

void	destroy_mutex(t_table *table);
void    destroy_end_mutex(t_table *table);
void	print_free(t_table *table);
void	join_child_threads(t_table *table);

// mutex control
void    set_end_simulation(t_table *table, bool value);
bool	get_end_simulation(t_table *table);
void	update_last_meal(t_philo *philo, long time);
void 	lock_eating_mutex(t_philo *philo, bool value);
void unlock_eating_mutex(t_philo *philo, bool value);

#endif