/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_feast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:26:14 by misargsy          #+#    #+#             */
/*   Updated: 2024/02/02 03:25:13 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	action_eat(t_philo *philo, const int left, const int right)
{
	pthread_mutex_lock(&(philo->mutex));
	philo->lasteat = philo_time();
	pthread_mutex_unlock(&(philo->mutex));
	if (!philo_logs(EATING, philo))
		return (false);
	philo_sleep(philo->config->eatspan);
	pthread_mutex_unlock(&(philo->config->forks[left].mutex));
	pthread_mutex_unlock(&(philo->config->forks[right].mutex));
	pthread_mutex_lock(&(philo->mutex));
	philo->eatcount++;
	pthread_mutex_unlock(&(philo->mutex));
	return (true);
}

static bool	action_think(t_philo *philo, const int left, const int right)
{
	if (!philo_logs(THINKING, philo))
		return (false);
	pthread_mutex_lock(&(philo->config->forks[right].mutex));
	pthread_mutex_lock(&(philo->config->forks[left].mutex));
	if (!philo_logs(FORK, philo) || !philo_logs(FORK, philo))
		return (false);
	return (true);
}

static bool	action_sleep(t_philo *philo)
{
	if (!philo_logs(SLEEPING, philo))
		return (false);
	philo_sleep(philo->config->sleepspan);
	return (true);
}

static void	initial_think(t_philo *philo, int population, int id)
{
	const int	simul_eats = (population - 1) / 2;

	if (population % 2 == 0)
	{
		if (id % 2 == 0)
			philo_sleep(philo->config->eatspan);
	}
	else
	{
		if (id % 2 == 0)
			philo_sleep(((float)(2.0 * philo->config->population - id)
					* philo->config->eatspan) / ((float)simul_eats * 2.0));
		else
			philo_sleep(((float)(philo->config->population - id)
					* philo->config->eatspan) / ((float)simul_eats * 2.0));
	}
	pthread_mutex_lock(&(philo->config->forks[id % population].mutex));
	if (!philo_logs(FORK, philo))
		return ;
	if (philo->config->population == 1)
		return ;
	pthread_mutex_lock(&(philo->config->forks[id - 1].mutex));
	if (!philo_logs(FORK, philo))
		return ;
}

void	*philo_feast(void *arg)
{
	t_philo			*philo;
	const int		left = ((t_philo *)arg)->id - 1;
	const int		right = ((t_philo *)arg)->id
		% ((t_philo *)arg)->config->population;

	philo = (t_philo *)arg;
	philo_sleep(philo->config->start - philo_time());
	if (!philo_logs(THINKING, philo))
		return (NULL);
	initial_think(philo, philo->config->population, philo->id);
	if (philo->config->population == 1)
		return (NULL);
	while (true)
	{
		if (!action_eat(philo, left, right)
			|| !action_sleep(philo) || !action_think(philo, left, right))
		{
			pthread_mutex_unlock(&(philo->config->forks[right].mutex));
			pthread_mutex_unlock(&(philo->config->forks[left].mutex));
			break ;
		}
	}
	return (NULL);
}
