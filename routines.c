/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:19:53 by lufiguei          #+#    #+#             */
/*   Updated: 2025/02/01 11:19:55 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_eat(t_philo *philo);
static void	*philo_think(t_philo *philo);
static void	*philo_sleep(t_philo *philo);
static int	check_end(t_table *table);
static void	update_end(t_table *table);

static void	print_routine(t_philo *philo, int routine);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(1);
	while (1)
	{
		if (check_end(philo->table) == 1)
			return (NULL);
		if (!philo->full)
			philo_eat(philo);
		if (philo->full)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
    t_table	*table;
    int		i;
    int		full;
    long	time_since_last_meal;

	table = (t_table *)arg;
	while (1)
	{
		if (check_end(table) == 1)
			return (NULL);
		i = -1;
		full = 0;
		while (++i < table->philo_nbr)
		{
			pthread_mutex_lock(&table->philos[i].meal_lock);
			time_since_last_meal = get_current_time() - table->philos[i].last_meal_time;
			pthread_mutex_unlock(&table->philos[i].meal_lock);
			if (check_end(table) == 1)
				return (NULL);
			if (time_since_last_meal >= table->time_die && table->philos[i].full == 0)
				return (update_end(table), print_routine(&table->philos[i], 4), NULL);
			pthread_mutex_lock(&table->philos[i].meal_lock);
			if (table->philos[i].full)
				full++;
			pthread_mutex_unlock(&table->philos[i].meal_lock);
		}
		if (full == table->philo_nbr)
			return (update_end(table), write(1, "All Philosophers have eaten, ending simulation.\n", 49), NULL);
		precise_usleep(1);
	}
	return (NULL);
}

static void	*philo_eat(t_philo *philo)
{
	if (check_end(philo->table) == 1)
		return (NULL);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left->fork);
		pthread_mutex_lock(&philo->right->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->right->fork);
		pthread_mutex_lock(&philo->left->fork);
	}
	print_routine(philo, 1);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time(); // what do i do??
	precise_usleep(philo->table->time_eat);
	philo->last_meal_time = get_current_time(); // or here
	philo->meals += 1;
	if (philo->meals == philo->table->max_meals && philo->table->max_meals != 0)
		philo->full = 1;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->right->fork);
	return (NULL);
}

static void	*philo_think(t_philo *philo)
{
	// long	time_left;

	if (check_end(philo->table) == 1)
		return (NULL);
	// pthread_mutex_lock(&philo->meal_lock);
	// time_left = philo->table->time_die - get_current_time() - philo->last_meal_time;
	// pthread_mutex_unlock(&philo->meal_lock);
	// if (time_left > philo->table->time_eat)
	// {
		print_routine(philo, 3);
		precise_usleep(1);
		//precise_usleep(time_left / 2);
	// }
	return (NULL);
}

static void	*philo_sleep(t_philo *philo)
{
	if (check_end(philo->table) == 1)
		return (NULL);
	print_routine(philo, 2);
	precise_usleep(philo->table->time_sleep);
	return (NULL);
}

static int	check_end(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->lock);
	end = table->end;
	pthread_mutex_unlock(&table->lock);
	return (end);
}

static void	update_end(t_table *table)
{
	pthread_mutex_lock(&table->lock);
	table->end = 1;
	pthread_mutex_unlock(&table->lock);
}

static void	print_routine(t_philo *philo, int routine)
{
	long	time;

	pthread_mutex_lock(&philo->table->lock);
	time = get_current_time() - philo->table->start;
	if (routine == 1)
		printf("%ld Philosopher %d is eating.\n", time, philo->id);
	else if (routine == 2)
		printf("%ld Philosopher %d is sleeping.\n", time, philo->id);
	else if (routine == 3)
		printf("%ld Philosopher %d is thinking.\n", time, philo->id);
	else if (routine == 4)
		printf("%ld Philosopher %d has died.\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->lock);
}