/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:19:10 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/22 13:19:11 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// to do :
// check how monitor reads if a philo is eating, and how it assumes death
// a philo eating cannot starve, but the timer only starts couting when
// they finish eating.
// do a dead lock for monitor, so if it checks and any philo is dead, 
// it locks everything to kill the simulation
// check timing problems, sometimes killing philo

static int	cleanup(t_table *table);
static int	create_and_join(t_table *table);

int	main(int argc, char **argv)
{
	t_table	table;

	if (parsing(&table, argv, argc) == 0)
	{
		init(&table);
		create_and_join(&table);
		cleanup(&table);
	}
	return (0);
}

static int	cleanup(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
		if (pthread_mutex_destroy(&table->forks[i].fork) != 0)
			return (printf("Error: mutex_destroy.\n"), 1);
	free (table->forks);
	i = -1;
	while (++i < table->philo_nbr)
		if (pthread_mutex_destroy(&table->philos[i].meal_lock) != 0)
			return (printf("Error: mutex_destroy.\n"), 1);
	free (table->philos);
	if (pthread_mutex_destroy(&table->lock) != 0)
		return (printf("Error: mutex_destroy.\n"), 1);
	return (0);
}

static int	create_and_join(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor, table) != 0)
		return (printf("Error: monitor thread create.\n"), 1);
	i = -1;
	while (++i < table->philo_nbr)
		if (pthread_create(&table->philos[i].thread_id, NULL,
				&routine, &table->philos[i]) != 0)
			return (printf("Error: thread create.\n"), cleanup(table), 1);
	if (pthread_join(monitor_thread, NULL) != 0)
		return (printf("Error: monitor join.\n"), cleanup(table), 1);
	i = -1;
	while (++i < table->philo_nbr)
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			return (printf("Error: thread join.\n"), cleanup(table), 1);
	return (0);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(long duration)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < duration)
		usleep(100);
}
