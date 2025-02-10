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

static void	cleanup(t_table *table);
static int	init(t_table *table);
static void	init_philo(t_table *table);

int	main(int argc, char **argv)
{
	t_table	table;

	if (parsing(&table, argv, argc) == 0)
	{
		init(&table);
		cleanup(&table);
	}
	return (0);
}

static int	init(t_table *table)
{
	int	i;

	table->end = 0; // fim da simulacao = end == 1;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos == NULL)
		return (printf("Error: Memory allocation.\n"), 1);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->forks == NULL)
		return (printf("Error: Memory allocation.\n"), 1);
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (printf("Error: mutex_init\n"), 1);
		table->forks[i].id = i; // conta a iniciar do 0;
	}
	init_philo(&table);
	return (0);
}
// if odd philo, pick left first
// if even philo, pick right first
static void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos.id = i + 1; // conta a partir do 1;
		table->philos.meals = 0;
		table->philos.full = 0; // se chegar ao max meals, para de comer e espera acabar a simulacao
		if (i % 2 == 0)
		{
			table->philos.right = &table->forks[table->philos.id - 1];
			table->philos.left = &table->forks[table->philos.id % table->philo_nbr];
		}
		else if (i % 2 != 0)
		{
			table->philos.left = &table->forks[table->philos.id % table->philo_nbr];
			table->philos.right = &table->forks[table->philos.id - 1];
		}
	}
}

static int	cleanup(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_destroy(&table->forks[i].fork) != 0)
			return (printf("Error: mutex_destroy.\n"), 1);
		free (table->forks[i]); // confirmar se é preciso dar free em cada fork
	}
	free (table->forks);
	i = -1;
	while (++i < table->philo_nbr)
	{	
		if (pthread_detach(&table->philos[i].thread_id) != 0)
			return (prinf("Error: detach_thread.\n"), 1);
		free(table->philos[i]); // confirmar se é preciso dar free em cada philo
	}
	free (table->philos);
	return (0);
}

/*
int	i;

i = -1;
while (++i < table->philo_nbr)
	if (pthread_create(&table->philos[i].thread_id, NULL, &monitor, NULL) != 0)
		return (printf("Error: thread create.\n"), 1);
i = -1;
while (++i < table->philo_nbr)
	if (pthread_join(&table->philos[i].thread_id, NULL) != 0)
		return (printf("Error: thread join.\n"), 1);
*/

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
