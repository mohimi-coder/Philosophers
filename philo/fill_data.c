/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:30:25 by mohimi            #+#    #+#             */
/*   Updated: 2024/08/12 16:02:11 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

static void	*monitoring(t_philo *philo, t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (pthread_mutex_lock(philo[i].dead_mutex)
				|| pthread_mutex_lock(philo[i].print_mutex))
				return (NULL);
			if (get_curent_time() - philo[i].last_meal >= (size_t)(data->ttd))
			{
				printf("%zu %d %s\n", get_curent_time() - philo[i].data->start,
					philo[i].id, "died");
				return (data->dead = 1, NULL);
			}
			pthread_mutex_unlock(philo[i].print_mutex);
			pthread_mutex_unlock(philo[i].dead_mutex);
			pthread_mutex_lock(philo[i].eat_mutex);
			if (data->eaten >= data->nb_philo)
				return (NULL);
			pthread_mutex_unlock(philo[i].eat_mutex);
		}
	}
	return (NULL);
}

int	ft_simulation(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
		if (pthread_detach(philo[i].thread))
			return (1);
	}
	monitoring(philo, data);
	return (0);
}

static int	fill_data(t_data *data, char **av)
{
	data->nb_philo = ft_atoi(av[1]).number;
	data->ttd = ft_atoi(av[2]).number;
	data->tte = ft_atoi(av[3]).number;
	data->tts = ft_atoi(av[4]).number;
	if (av[5])
		data->nb_must_eat = ft_atoi(av[5]).number;
	else
		data->nb_must_eat = -1;
	data->dead = 0;
	data->eaten = 0;
	data->start = get_curent_time();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL)
		|| pthread_mutex_init(&data->dead_mutex, NULL)
		|| pthread_mutex_init(&data->eat_mutex, NULL))
		return (1);
	return (0);
}

int	ft_fill(t_philo **philo, t_data *data, char **av)
{
	int	i;

	i = -1;
	if (fill_data(data, av))
		return (1);
	*philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philo)
		return (1);
	while (++i < data->nb_philo)
	{
		1 && ((*philo)[i].id = i + 1, (*philo)[i].data = data);
		(*philo)[i].meals = 0;
		(*philo)[i].last_meal = data->start;
		(*philo)[i].start = data->start;
		(*philo)[i].print_mutex = &data->print_mutex;
		(*philo)[i].dead_mutex = &data->dead_mutex;
		(*philo)[i].eat_mutex = &data->eat_mutex;
		(*philo)[i].right_fork = &data->forks[i];
		(*philo)[i].left_fork = &data->forks[(i + 1) % data->nb_philo];
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
	}
	if ((ft_simulation(*philo, data)))
		return (1);
	return (ft_free(*philo, data), 0);
}
