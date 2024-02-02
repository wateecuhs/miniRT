/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:21:11 by panger            #+#    #+#             */
/*   Updated: 2024/02/02 14:13:41 by panger           ###   ########.fr       */
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
	rest = ft_atoi(&str[dot + 1]);
	ret += (float)(rest * 0.1);
	return (ret);
}

int	get_rgb(char *str, t_colors *ret)
{
	int	tmp;
	int	i;
	char	**arr;

	arr = ft_split(str, ",");
	if (!arr)
		return (-1);
	if (ft_arrlen(arr) != 3)
		return (free_arr(arr), 0);
	i = 0;
	while (i < 3)
	{
		tmp = ft_atoi(arr[i]);
		if (tmp < 0 || tmp > 255)
			return (free_arr(arr), 0);
		if (i == 0)
			ret->r = tmp;
		else if (i == 1)
			ret->g = tmp;
		else if (i == 2)
			ret->b = tmp;
		i++;
	}
	return (free_arr(arr), 1);
}

int	get_coords(char *str, t_coords *ret)
{
	int	tmp;
	int	i;
	char	**arr;

	arr = ft_split(str, ",");
	if (!arr)
		return (-1);
	if (ft_arrlen(arr) != 3 || !is_float(arr[0])
		|| !is_float(arr[1]) || !is_float(arr[2]))
		return (free_arr(arr), 0);
	i = 0;
	while (i < 3)
	{
		tmp = ft_atof(arr[i]);
		if (tmp < 0 || tmp > 255)
			return (free_arr(arr), 0);
		if (i == 0)
			ret->x = tmp;
		else if (i == 1)
			ret->y = tmp;
		else if (i == 2)
			ret->z = tmp;
		i++;
	}
	return (free_arr(arr), 1);
}
