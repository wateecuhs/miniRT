/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:21:11 by panger            #+#    #+#             */
/*   Updated: 2024/02/20 13:00:10 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	tot;
	int	sign;

	i = 0;
	tot = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		tot = tot * 10 + (nptr[i] - 48);
		i++;
	}
	return (tot * sign);
}

double	ft_atof(char *str)
{
	double	ret;
	int		dot;
	int		rest;

	ret = (double)ft_atoi(str);
	dot = ft_strchr(str, '.');
	if (dot == -1)
		return (ret);
	rest = ft_atoi(&str[dot + 1]);
	ret += (double)(rest * 0.1);
	return (ret);
}
