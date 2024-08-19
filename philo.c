/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:05:26 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/19 18:43:44 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int arc, char **arv)
{
	t_table	*table;

	table = NULL;
	if (arc == 5 || arc == 6)
	{
		table = parsing_arv(arc, arv);
		monitor_threads(table);
	}
	else
		error_mess("Input should be [5 200 200 300] or [5 200 200 300 [5]]");
	return (0);
}
