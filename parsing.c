/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:36:34 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/22 13:36:44 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	argument_error(void)
{
	printf("Wrong number of arguments. Try:\n\'");
	printf("./philo\'\n\"Number_of_philosophers\"\n\"Time_to_die");
	printf("\"\n\"Time_to_eat\"\n\"Time_to_sleep\"\n\"Number_of_");
	printf("time_each_philosopher_must_eat\"      *[Optional]*\n");
	return (1);
}

static long	ft_atol(const char *nptr)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
		return (printf("Error: negative number.\n"), 1);
	if (nptr[i] < '0' || nptr[i] > '9')
		return (printf("Error: Argument isnt a number.\n"), 1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	if (result > INT_MAX)
		return (printf("Error: INT_MAX.\n"), 1);
	return (result);
}

int	parsing(t_table *table, char **argv, int argc)
{
	if (argc > 6 || argc < 5)
		return (argument_error(), 1);
	table->philo_nbr = ft_atol(argv[1]);
	table->time_die = ft_atol(argv[2]);
	table->time_eat = ft_atol(argv[3]);
	table->time_sleep = ft_atol(argv[4]);
	if (table->time_eat < 60 || table->time_sleep < 60
		|| table->time_die < 60)
		return (printf("Error: Time not greater than  60ms.\n"), 1);
	if (table->philo_nbr < 1)
		return (printf("Error: Number of Philosophers can't be 0 >=.\n"), 1);
	if (argv[5])
	{
		table->max_meals = ft_atol(argv[5]);
		if (table->max_meals == 0)
			return (printf("You really want them to starve, dont you?\n"), 1);
	}
	else
		table->max_meals = -1;
	if (table->philo_nbr == 1)
		return (printf("Philosopher 1 has only one fork and will starve.\n"),
			precise_usleep(table->time_die), printf("Philo 1 died.\n"), 1);
	if (table->time_die < table->time_eat + table->time_sleep)
		return (printf("Error:Time to die need to be > than sleep+eat.\n"), 1);
	return (0);
}

static void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals = 0;
		table->philos[i].full = 0;
		table->philos[i].last_meal_time = table->start;
		table->philos[i].table = table;
		table->philos[i].left = &table->forks[i];
		if (i == 0)
			table->philos[i].right = &table->forks[table->philo_nbr - 1];
		else
			table->philos[i].right = &table->forks[i - 1];
		pthread_mutex_init(&table->philos[i].meal_lock, NULL);
	}
}

int	init(t_table *table)
{
	int	i;

	table->end = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos == NULL)
		return (printf("Error: Memory allocation.\n"), 1);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->forks == NULL)
		return (printf("Error: Memory allocation.\n"), free(table->philos), 1);
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (printf("Error: mutex_init.\n"), 1);
		table->forks[i].id = i;
	}
	if (pthread_mutex_init(&table->lock, NULL) != 0)
		return (printf("Error: mutex_init.\n"), 1);
	table->start = get_current_time();
	init_philo(table);
	return (0);
}
