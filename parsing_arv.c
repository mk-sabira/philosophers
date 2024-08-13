/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:12:23 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/13 15:06:23 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_nb(char *str)
{
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	long long	r;
	long long	x;
	int			s;

	s = 1;
	r = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		x = r;
		r = r * 10 + (*str - '0') * s;
		str++;
		if ((r > x) && (s < 0))
			return (0);
		if ((r < x) && (s > 0))
			return (-1);
	}
	return (r);
}

t_table *parsing_arv(int arc, char **arv)
{
	int		i;
	t_table	*table;

	i = 1;
	table = init_table();
	while (i < arc)
	{
		if (!(is_valid_nb(arv[i])))
		{
			printf("not valid nb");
			exit(1);
		}
		i++;
	}
	pthread_mutex_lock(&table->start_simul_mutex);
	table = fill_table_struct(arv, table);
	pthread_mutex_unlock(&table->start_simul_mutex);
	return (table);
}
