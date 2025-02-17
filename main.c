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
// create and joins all threads, monitor and philos
static int create_and_join(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor, table) != 0)
		return (printf("Error: monitor thread create.\n"), 1);
	i = -1;
	while (++i < table->philo_nbr)
		if (pthread_create(&table->philos[i].thread_id, NULL, &routine, &table->philos[i]) != 0)
			return (printf("Error: thread create.\n"), cleanup(table), 1);
	if (pthread_join(monitor_thread, NULL) != 0)
			return (printf("Error: monitor join.\n"), cleanup(table), 1);
	i = -1;
	while (++i < table->philo_nbr)
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			return (printf("Error: thread join.\n"), cleanup(table), 1);
	return (0);
}

long	get_current_time()
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
		usleep(500);
}

/*
time to die starts since the beggining of the program, if a philosopher isnt 
eating. time to eat, during this time the philo will hold 2 forks, the left
and the right one. time to sleep after eating?
simulation stops when a phil die
they sit in a circle, so phil N, sits besides N + 1 and N - 1.
Phil 1 sits next to N - 1 (number of phil) and N + 1 (next) USE A CIRCULAR
Linked list?
use a monitor to get info in between the philosophers
when eating, get time of last meal, so to do a priority in what phil must eat
the monitor checks the availability of forks and the priority list
do a function for each routine, so a function for eating, one for sleeping and one for thinking
distinguish philosophers between odd and even? i % 2 = 0
*/

/*   Phil 1 is next to phil + 1 and phil % philnumbr + 1
		 DINNER READY
			phil 2
		f1	    	f2
	Phil1		      phil 3
	    f0          f3
	  phil 5  f4  phil 4

*/