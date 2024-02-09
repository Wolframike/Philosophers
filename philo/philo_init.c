/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:24:43 by misargsy          #+#    #+#             */
/*   Updated: 2024/02/02 02:58:22 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	philo_struct_fill(t_philo *philo, t_config *config, char **argv)
{
	int	i;

	config->start = philo_time() + 1000;
	i = -1;
	while (++i < config->population)
	{
		if (pthread_mutex_init(&(philo[i].mutex), NULL) != 0)
			return (false);
		philo[i].id = i + 1;
		philo[i].config = config;
		philo[i].eatcount = 0;
		philo[i].lasteat = config->start;
	}
	config->lifespan = ft_atoi(argv[2]);
	config->eatspan = ft_atoi(argv[3]);
	config->sleepspan = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		config->maxeat = ft_atoi(argv[5]);
	else
		config->maxeat = -1;
	if (config->lifespan <= 0 || config->eatspan <= 0
		|| config->sleepspan <= 0 || config->maxeat == 0)
		return (false);
	return (true);
}

static bool	philo_fork_init(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->population)
	{
		config->forks[i].id = i + 1;
		if (pthread_mutex_init(&(config->forks[i].mutex), NULL) != 0)
			return (false);
	}
	return (true);
}

bool	philo_init(t_philo **philo, char **argv)
{
	t_config	*config;

	config = (t_config *)malloc(sizeof(t_config));
	if (config == NULL)
		return (false);
	if (pthread_mutex_init(&(config->mutex), NULL) != 0
		|| pthread_mutex_init(&(config->outstream), NULL) != 0)
		return (free(config), false);
	config->dismiss = false;
	config->population = ft_atoi(argv[1]);
	if (config->population < 1)
		return (free(config), false);
	(*philo) = (t_philo *)malloc(sizeof(t_philo) * config->population);
	if ((*philo) == NULL)
		return (free(config), false);
	if (!philo_struct_fill(*philo, config, argv))
		return (free(config), free(*philo), false);
	config->forks = (t_fork *)malloc(sizeof(t_fork) * config->population);
	if (config->forks == NULL || !philo_fork_init(config))
		return (free(config), free(*philo), free(config->forks), false);
	return (true);
}
