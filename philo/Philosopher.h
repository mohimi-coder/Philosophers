/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:54:43 by mohimi            #+#    #+#             */
/*   Updated: 2024/08/07 10:11:47 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# ifndef MAX_PHIL
#  define MAX_PHIL 200
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_ptr
{
	long long	number;
	int			over_fl;
}				t_ptr;

typedef struct s_data
{
	int				dead;
	int				nb_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				eaten;
	int				nb_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	eat_mutex;
	size_t			start;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	size_t			start;
	size_t			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*eat_mutex;
	int				meals;
	t_data			*data;
}					t_philo;

t_ptr	ft_atoi(const char *str);
int		parce_input(int ac, char **av);
void	*routine(void *arg);
int		ft_fill(t_philo **philo, t_data *data, char **av);
size_t	get_curent_time(void);
void	ft_usleep(size_t time);
int		ft_error_message(char *mess);
void	ft_free(t_philo *philo, t_data *data);

#endif