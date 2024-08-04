/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:12:23 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/04 13:14:56 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_nb(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-')
		str++;
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
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

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("Eroor\n");
		exit(1);
	}
	data->nb_philo = 0;
	data->die = 0;
	data->eat = 0;
	data->sleep = 0;
	data->each_ph = 0;
	return (data);
}

t_data	*fill_data(char **arv)
{
	t_data	*data;

	data = init_data();
	data->nb_philo = ft_atoi(arv[1]);
	data->die = ft_atoi(arv[2]);
	data->eat = ft_atoi(arv[3]);
	data->sleep = ft_atoi(arv[4]);
	data->each_ph = ft_atoi(arv[5]);
	return (data);
}

t_data	*parsing_arv(int arc, char **arv)
{
	int		i;
	t_data	*data;

	i = 1;
	while (i < arc)
	{
		if (!(is_valid_nb(arv[i])))
		{
			printf("not valid nb");
		}
		i++;
	}
	data = fill_data(arv);
	return (data);
}
