/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:17:26 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/20 14:04:04 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_LIB_H
# define PHILO_LIB_H

# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *str1, const char *str2);
bool	ft_isdigit(int c);
size_t	ft_strlen(const char *str);

#endif