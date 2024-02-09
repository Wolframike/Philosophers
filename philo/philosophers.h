/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:20:10 by misargsy          #+#    #+#             */
/*   Updated: 2024/02/02 02:58:04 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <stdint.h>

# include "philo_lib.h"

# define FORK "%lld %d has taken a fork\n"
# define EATING "%lld %d is eating\n"
# define SLEEPING "%lld %d is sleeping\n"
# define THINKING "%lld %d is thinking\n"
# define DIED "%lld %d died\n"

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}	t_fork;

typedef struct s_config
{
	pthread_mutex_t		mutex;
	pthread_mutex_t		outstream;
	int					population;
	int					lifespan;
	int					eatspan;
	int					sleepspan;
	int					maxeat;
	uint64_t			start;
	struct s_fork		*forks;
	pthread_t			monitorer;
	bool				dismiss;
}	t_config;

typedef struct s_philo
{
	struct s_config	*config;
	pthread_mutex_t	mutex;
	pthread_t		pthread;
	int				eatcount;
	uint64_t		lasteat;
	int				id;
}	t_philo;

//philo_parse.c
bool		philo_parse(int argc, char **argv);

//philo_utils.c
int			philo_error(void);
int			philo_free(t_philo *philo);
uint64_t	philo_time(void);
void		philo_sleep(int64_t time);
bool		check_dismiss(t_philo *philo);
//philo_init.c
bool		philo_init(t_philo **philo, char **argv);

//philo_feast.c
void		*philo_feast(void *arg);

//philo_logs.c
bool		philo_logs(const char *str, t_philo *philo);

#endif
