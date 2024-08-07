/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:05:26 by bmakhama          #+#    #+#             */
/*   Updated: 2024/08/07 17:26:16 by bmakhama         ###   ########.fr       */
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
		fill_table_struct(arv, table);
		print_table(table);
	}
	else
		error_mess("Input should be [5 200 200 300] or [5 200 200 300 [5]]");
	return (0);
}
