/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lib_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:25:47 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/20 14:04:00 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_lib.h"

static long	numcatch(const char *str)
{
	long	n;
	long	m;

	n = 0;
	while (('0' <= *str) && (*str <= '9'))
	{
		m = n;
		n = n * 10 + (*str - '0');
		if (n < m)
			return (-1);
		str++;
	}
	return (n);
}

int	ft_atoi(const char *str)
{
	long	val;
	int		sign;

	val = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if ('0' <= *str && *str <= '9')
		val = numcatch(str);
	if (val == -1)
	{
		if (sign < 0)
			return ((int)LONG_MIN);
		return ((int)LONG_MAX);
	}
	return ((int)(val * sign));
}
