/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:11:28 by misargsy          #+#    #+#             */
/*   Updated: 2024/02/07 16:38:41 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	thenightisover(t_philo *philo)
{
	int			i;
	const bool	validmaxeat = philo[0].config->maxeat > 0;
	bool		full;

	i = -1;
	full = true;
	while (++i < philo->config->population)
	{
		pthread_mutex_lock(&(philo[i].mutex));
		if (full && (philo[i].eatcount >= philo[i].config->maxeat)
			&& validmaxeat)
			full = true;
		else
			full = false;
		if (philo_time() - philo[i].lasteat
			> (uint64_t)philo[i].config->lifespan)
		{
			philo_logs(DIED, &philo[i]);
			pthread_mutex_unlock(&(philo[i].mutex));
			return (true);
		}
		pthread_mutex_unlock(&(philo[i].mutex));
	}
	return (full);
}

static void	*monitorer(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo_sleep(philo->config->start - philo_time());
	while (true)
	{
		if (thenightisover(philo))
		{
			pthread_mutex_lock(&(philo->config->mutex));
			philo->config->dismiss = true;
			pthread_mutex_unlock(&(philo->config->mutex));
			return (NULL);
		}
	}
}

static bool	philo_create(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].config->population)
		if (pthread_create(&(philo[i].pthread), NULL,
				philo_feast, &philo[i]) != 0)
			return (false);
	if (pthread_create(&(philo[0].config->monitorer),
			NULL, monitorer, philo) != 0)
		return (false);
	return (true);
}

static bool	philo_join(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].config->population)
	{
		if (pthread_join(philo[i].pthread, NULL) != 0)
			return (false);
	}
	if (pthread_join(philo[0].config->monitorer, NULL) != 0)
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;

	if (!philo_parse(argc, argv))
		return (philo_error());
	philo = NULL;
	if (!philo_init(&philo, argv))
		return (philo_error());
	if (!philo_create(philo))
		return (philo_free(philo), philo_error());
	if (!philo_join(philo))
		return (philo_free(philo), philo_error());
	return (philo_free(philo));
}
