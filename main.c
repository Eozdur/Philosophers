/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:13:27 by eozdur            #+#    #+#             */
/*   Updated: 2023/06/23 17:24:40 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philo)
	{
		if (table->number_of_philo == 1)
			pthread_detach(table->philos[i].thread);
		pthread_join(table->philos[i].thread, NULL);
	}
	pthread_mutex_destroy(&table->stop_count);
	pthread_mutex_destroy(&table->count_eat);
	pthread_mutex_destroy(&table->eat_last);
	pthread_mutex_destroy(&table->is_die);
	pthread_mutex_destroy(&table->is_print);
	i = 0;
	while (i < table->number_of_philo)
		pthread_mutex_destroy(&table->forks[i++]);
	free(table->forks);
	free(table->philos);
	free(table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = parse(ac, av);
	if (table != NULL)
	{
		start_threads(table);
		end_threads(table);
	}
	return (0);
}
