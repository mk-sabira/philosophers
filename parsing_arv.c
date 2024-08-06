/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:12:23 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/06 12:20:37 by bmakhama         ###   ########.fr       */
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

t_table	*init_data(void)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
	{
		printf("Eroor\n");
		exit(1);
	}
	table->nb_philo = 0;
	table->die = 0;
	table->eat = 0;
	table->sleep = 0;
	table->nb_meal = 0;
	return (table);
}

t_table	*fill_data(char **arv)
{
	t_table	*table;

	table = init_data();
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
	return (table);
}

t_table	*parsing_arv(int arc, char **arv)
{
	int		i;
	t_table	*table;

	i = 1;
	while (i < arc)
	{
		if (!(is_valid_nb(arv[i])))
		{
			printf("not valid nb");
			exit(1);
		}
		i++;
	}
	table = fill_data(arv);
	return (table);
}
