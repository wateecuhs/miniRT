/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:21:11 by panger            #+#    #+#             */
/*   Updated: 2024/02/05 11:07:58 by panger           ###   ########.fr       */
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

float	ft_atof(char *str)
{
	float	ret;
	int		dot;
	int		rest;

	ret = (float)ft_atoi(str);
	dot = ft_strchr(str, '.');
	if (dot == -1)
		return (ret);
	rest = ft_atoi(&str[dot + 1]);
	ret += (float)(rest * 0.1);
	return (ret);
}
