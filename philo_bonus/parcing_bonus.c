/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:52:22 by mohimi            #+#    #+#             */
/*   Updated: 2024/08/06 12:20:03 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

t_ptr	ft_atoi(const char *str)
{
	int		i;
	t_ptr	rslt;

	i = 0;
	1 && (i = 0, rslt.number = 0, rslt.over_fl = 0);
	if (!str)
		return ((t_ptr){-1, 0});
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt.number = rslt.number * 10 + (str[i] - 48);
		if ((rslt.number > 2147483647 || rslt.number < -2147483648)
			|| (rslt.number < '0' && rslt.number > '9'))
			rslt.over_fl = 1;
		i++;
	}
	if (str[i] != '\0')
		return ((t_ptr){-1, 0});
	return ((t_ptr){rslt.number, rslt.over_fl});
}

int	parce_input(int ac, char **av)
{
	int		x;
	t_ptr	result;

	x = 1;
	if (ac < 5 || ac > 6)
		return (1);
	while (x < ac)
	{
		result = ft_atoi(av[x]);
		if (result.over_fl == 1 || (result.number <= 0 && x != '5'))
			return (1);
		if (x == 1 && result.number > MAX_PHIL)
			return (1);
		if ((x >= 2 && x <= 4) && result.number < 60)
			return (1);
		x++;
	}
	return (0);
}
