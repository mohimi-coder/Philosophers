/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:33:01 by mohimi            #+#    #+#             */
/*   Updated: 2024/08/11 12:05:40 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;
	int		i;

	i = -1;
	if (parce_input(ac, av) || init_data(&data, ac, av))
		return (printf("Error : parce or init data\n"), exit(1), 1);
	philo = malloc(sizeof(t_philo) * data.nb_philo);
	(!philo) && (printf("Error : malloc\n"), exit(1), i = 1);
	while (++i < data.nb_philo)
	{
		((philo[i].pid = fork()) < 0) && (printf("Error\n"), exit(1), i = 1);
		if (philo[i].pid == 0)
		{
			1 && (philo[i].id = i + 1, philo[i].data = &data);
			philo[i].last_meal = data.start;
			1 && (philo[i].start = data.start, philo[i].meals = 0);
			(pthread_create(&philo[i].thread, NULL, &monitoring, &philo[i]))
				&& (exit(1), i = 1);
			(pthread_detach(philo[i].thread)) && (exit(1), i = 1);
			routine(&philo[i]);
		}
	}
	return (wait_philos(philo, &data), free_things(philo, &data), exit(0), 0);
}
