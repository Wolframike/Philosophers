/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:12:37 by misargsy          #+#    #+#             */
/*   Updated: 2024/02/02 04:15:40 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_error(void)
{
	write(STDERR_FILENO, "Error\n", 6);
	return (EXIT_FAILURE);
}

int	philo_free(t_philo *philo)
{
	ssize_t	i;

	i = -1;
	while (++i < philo[0].config->population)
	{
		pthread_mutex_destroy(&(philo[0].config->forks[i].mutex));
		pthread_mutex_destroy(&(philo[i].mutex));
	}
	free(philo[0].config->forks);
	free(philo[0].config);
	free(philo);
	return (EXIT_SUCCESS);
}

uint64_t	philo_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000);
}

void	philo_sleep(int64_t time)

{
	const int64_t	until = philo_time() + time;
	int64_t			chunk;

	while (true)
	{
		chunk = (until - philo_time()) * 1000;
		if (chunk <= 0)
			break ;
		usleep(chunk / 2);
	}
}

bool	check_dismiss(t_philo *philo)
{
	bool	dismiss;

	pthread_mutex_lock(&(philo->config->mutex));
	dismiss = philo->config->dismiss;
	pthread_mutex_unlock(&(philo->config->mutex));
	return (dismiss);
}
