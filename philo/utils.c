/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:33:24 by mohimi            #+#    #+#             */
/*   Updated: 2024/08/12 16:00:50 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

static void	ft_print(t_philo *philo, char *str)
{
	if (pthread_mutex_lock(philo->dead_mutex))
		return ;
	if (philo->data->dead == 0)
	{
		if (pthread_mutex_lock(philo->print_mutex))
			return ;
		printf("%zu %d %s\n",
			get_curent_time() - philo->data->start, philo->id, str);
		pthread_mutex_unlock(philo->print_mutex);
	}
	pthread_mutex_unlock(philo->dead_mutex);
}

void	eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork))
		return ;
	ft_print(philo, "has taken a fork");
	if (pthread_mutex_lock(philo->right_fork))
		return ;
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	if (pthread_mutex_lock(philo->dead_mutex))
		return ;
	philo->last_meal = get_curent_time();
	pthread_mutex_unlock(philo->dead_mutex);
	philo->meals++;
	if (philo->meals == philo->data->nb_must_eat)
	{
		if (pthread_mutex_lock(philo->eat_mutex))
			return ;
		philo->data->eaten++;
		pthread_mutex_unlock(philo->eat_mutex);
	}
	ft_usleep(philo->data->tte);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;	

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->tte);
	while (philo->data->nb_must_eat == -1
		|| philo->meals < philo->data->nb_must_eat)
	{
		eat(philo);
		ft_print(philo, "is sleeping");
		ft_usleep(philo->data->tts);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}
