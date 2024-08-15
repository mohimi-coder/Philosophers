/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:53:58 by mohimi            #+#    #+#             */
/*   Updated: 2024/08/06 16:29:19 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

size_t	get_curent_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_curent_time();
	while (get_curent_time() - start < time)
		usleep(100);
}

int	ft_error_message(char *mess)
{
	int	i;

	i = 0;
	while (mess[i])
	{
		write (2, &mess[i], 1);
		i++;
	}
	write (2, "\n", 1);
	return (-1);
}
