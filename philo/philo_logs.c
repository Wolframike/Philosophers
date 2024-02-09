/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:25:58 by misargsy          #+#    #+#             */
/*   Updated: 2024/02/02 03:29:17 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_logs(const char *str, t_philo *philo)
{
	if (check_dismiss(philo))
	{
		return (false);
	}
	pthread_mutex_lock(&(philo->config->outstream));
	if (check_dismiss(philo))
	{
		pthread_mutex_unlock(&(philo->config->outstream));
		return (false);
	}
	printf(str, philo_time() - philo->config->start, philo->id);
	pthread_mutex_unlock(&(philo->config->outstream));
	return (true);
}
