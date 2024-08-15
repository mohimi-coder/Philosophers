/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:54:43 by mohimi            #+#    #+#             */
/*   Updated: 2024/08/05 18:48:29 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# ifndef MAX_PHIL
#  define MAX_PHIL 200

# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_ptr
{
	long long	number;
	int			over_fl;
}				t_ptr;

typedef struct s_data
{
	sem_t			*forks;
	sem_t			*print;
	sem_t			*dead;
	sem_t			*eat;
	int				nb_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				nb_must_eat;
	size_t			start;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	size_t			start;
	int				pid;
	size_t			last_meal;
	int				meals;
	t_data			*data;
}					t_philo;

t_ptr	ft_atoi(const char *str);
int		parce_input(int ac, char **av);
int		init_data(t_data *data, int ac, char **av);
void	ft_print(t_philo *philo, char *str);
size_t	get_time(void);
void	*routine(t_philo *philo);
void	ft_usleep(size_t time);
void	*monitoring(void *arg);
void	wait_philos(t_philo *philo, t_data *data);
void	free_things(t_philo *philo, t_data *data);

#endif