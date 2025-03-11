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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		precise_usleep(2);
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
	print_routine(philo, 5);
	print_routine(philo, 1);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->meals += 1;
	if (philo->meals == philo->table->max_meals && philo->table->max_meals != 0)
		philo->full = 1;
	pthread_mutex_unlock(&philo->meal_lock);
	precise_usleep(philo->table->time_eat);
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->right->fork);
	return (NULL);
}

static void	*philo_think(t_philo *philo)
{
	if (check_end(philo->table) == 1)
		return (NULL);
	print_routine(philo, 3);
	precise_usleep(1);
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

void	print_routine(t_philo *philo, int routine)
{
	long	time;

	pthread_mutex_lock(&philo->table->lock);
	time = get_current_time() - philo->table->start;
	if (routine == 4 && philo->table->end)
		printf("%ld Philosopher %d has died.\n", time, philo->id);
	else if (philo->table->end)
	{
		pthread_mutex_unlock(&philo->table->lock);
		return ;
	}
	else if (routine == 5)
		printf("%ld Philosopher %d has taken a fork.\n", time, philo->id);
	else if (routine == 1)
		printf("%ld Philosopher %d is eating.\n", time, philo->id);
	else if (routine == 2)
		printf("%ld Philosopher %d is sleeping.\n", time, philo->id);
	else if (routine == 3)
		printf("%ld Philosopher %d is thinking.\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->lock);
}
