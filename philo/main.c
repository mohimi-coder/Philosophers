/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:58:26 by mohimi            #+#    #+#             */
/*   Updated: 2024/08/12 19:29:52 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

void	ft_free(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	usleep(500000);
	pthread_mutex_unlock(&data->eat_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	while (++i < data->nb_philo)
	{
		pthread_mutex_unlock(&data->forks[i]);
		pthread_mutex_destroy(&data->forks[i]);
	}
	free(data->forks);
	data->forks = NULL;
	free(philo);
	data->nb_philo = 0;
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	data;

	if (parce_input(ac, av))
	{
		ft_error_message("ERROR: invalid input!");
		return (0);
	}
	if (ft_fill(&philo, &data, av))
	{
		ft_error_message("ERROR: malloc failed!");
		return (0);
	}
}
