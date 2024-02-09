/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lib_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:16:42 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/16 15:25:44 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_lib.h"

static int	dig(int n)
{
	int	d;

	d = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		d += 2;
		n /= -10;
	}
	while (n > 0)
	{
		d++;
		n /= 10;
	}
	return (d);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		d;

	d = dig(n);
	str = (char *)malloc(sizeof(char) * (d + 1));
	if (str == NULL)
		return (NULL);
	str[d] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		str[d-- - 1] = -(n % 10) + '0';
		n /= -10;
	}
	while (n > 0)
	{
		str[d-- - 1] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (((*str1 != '\0')) && (*str2 != '\0'))
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if ((*str1 == '\0') && (*str2 != '\0'))
		return (-(*str2));
	else if ((*str1 != '\0') && (*str2 == '\0'))
		return (*str1);
	return (0);
}

bool	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (true);
	return (false);
}

size_t	ft_strlen(const char *str)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}
