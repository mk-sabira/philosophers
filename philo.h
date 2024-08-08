/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:40:14 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/08 16:38:24 by bmakhama         ###   ########.fr       */
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
	t_chopstick *l_chopstick;
	t_chopstick *r_chopstick;
	pthread_t		thread_id;
	t_table		*table;
}	t_philo;


//all inputs
struct s_table
{
	long		nb_philo;
	long		die;
	long		eat;
	long		sleep;
	long		nb_meal;
	long		start_simulation;
	bool		end_simulation; // philo die or all full
	t_chopstick	*chopstick;
	t_philo 	*philo;
};

//parsing
t_table *parsing_arv(int arc, char **arv);
t_table    *init_table(void);
t_table	*fill_table_struct(char **arv, t_table	*table);
void    *philo_routine(void *arg);
long    get_current_time(void);
void print_info(t_table *table, int id, char *mess, char *color );
void monitor_threads(t_table *table);

//helper functions
long	ft_atoi(const char *str);
void    error_mess(char *str);
// void    cancel_threads(t_table *table);
void	destroy_mutex(t_table *table);


// delete later
void print_table(t_table *table);
#endif