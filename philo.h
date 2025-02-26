/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:19:19 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/22 13:19:20 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;	
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				meals;
	int				full;
	long			last_meal_time;
	t_fork			*left;
	t_fork			*right;
	pthread_t		thread_id;
	pthread_mutex_t	meal_lock;
	t_table			*table;
}					t_philo;

typedef struct s_table
{
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	lock;
	long			philo_nbr;
	long			time_eat;
	long			time_sleep;
	long			time_die;
	long			max_meals;
	long			start;
	int				end;
}					t_table;

void	*routine(void *arg);
void	*monitor(void *arg);
int		check_end(t_table *table);
void	print_routine(t_philo *philo, int routine);

int		parsing(t_table *table, char **argv, int argc);
int		init(t_table *table);
long	get_current_time(void);
void	precise_usleep(long duration);

#endif
