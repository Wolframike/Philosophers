/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:01:16 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/11 20:39:48 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	philo_isoverflow(char *str)
{
	size_t	len;
	char	*max;
	bool	overflow;

	len = ft_strlen(str);
	max = ft_itoa(INT_MAX);
	if (max == NULL)
		return (false);
	overflow = false;
	if (len > ft_strlen(max))
		overflow = true;
	if (len == ft_strlen(max) && (ft_strcmp(str, max) != 0))
		overflow = true;
	free(max);
	return (overflow);
}

static bool	philo_isvalidarg(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	if (philo_isoverflow(str))
		return (false);
	return (true);
}

bool	philo_parse(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (false);
	i = 1;
	while (i < argc)
	{
		if (!philo_isvalidarg(argv[i]))
			return (false);
		i++;
	}
	return (true);
}
