/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:23:01 by mohimi            #+#    #+#             */
/*   Updated: 2024/08/11 17:32:13 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_print(t_philo *philo, char *str)
{
	sem_wait(philo->data->print);
	printf("%zu %d %s\n", get_time() - philo->data->start, philo->id, str);
	if (ft_strcmp(str, "died"))
		sem_post(philo->data->print);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

int	init_data(t_data *data, int ac, char **av)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("eat");
	data->nb_philo = ft_atoi(av[1]).number;
	data->ttd = ft_atoi(av[2]).number;
	data->tte = ft_atoi(av[3]).number;
	data->tts = ft_atoi(av[4]).number;
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]).number;
	else
		data->nb_must_eat = -1;
	data->start = get_time();
	data->forks = sem_open("forks", O_CREAT, 0660, data->nb_philo);
	data->print = sem_open("print", O_CREAT, 0660, 1);
	data->dead = sem_open("dead", O_CREAT, 0660, 1);
	data->eat = sem_open("eat", O_CREAT, 0660, 1);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED
		|| data->dead == SEM_FAILED || data->eat == SEM_FAILED)
		return (1);
	if (data->nb_philo > MAX_PHIL || data->ttd < 60
		|| data->tte < 60 || data->tts < 60)
		return (1);
	return (0);
}
