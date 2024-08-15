/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:52:24 by mohimi            #+#    #+#             */
/*   Updated: 2024/08/05 18:43:12 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

void	wait_philos(t_philo *philo, t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < data->nb_philo)
				kill(philo[i].pid, SIGKILL);
			break ;
		}
	}
}

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->dead);
		if (get_time() - philo->last_meal >= (size_t)(philo->data->ttd))
		{
			ft_print(philo, "died");
			exit(1);
		}
		ft_usleep(1);
		sem_post(philo->data->dead);
	}
}

void	*routine(t_philo *philo)
{
	while (philo->data->nb_must_eat == -1
		|| philo->meals < philo->data->nb_must_eat)
	{
		sem_wait(philo->data->forks);
		ft_print(philo, "has taken a fork");
		sem_wait(philo->data->forks);
		ft_print(philo, "has taken a fork");
		ft_print(philo, "is eating");
		sem_wait(philo->data->eat);
		philo->last_meal = get_time();
		sem_post(philo->data->eat);
		philo->meals++;
		ft_usleep(philo->data->tte);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		ft_print(philo, "is sleeping");
		ft_usleep(philo->data->tts);
		ft_print(philo, "is thinking");
	}
	exit (0);
}

void	free_things(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		kill(philo[i].pid, SIGKILL);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->dead);
	sem_close(data->eat);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("eat");
	free(philo);
}
