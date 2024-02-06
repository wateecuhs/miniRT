/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:28:10 by panger            #+#    #+#             */
/*   Updated: 2024/02/05 13:04:11 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_rgb(char *str, t_colors *ret)
{
	int		tmp;
	int		i;
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
	int		tmp;
	int		i;
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

int	get_vector(char *str, t_coords *ret)
{
	int		tmp;
	int		i;
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
		if (tmp < -1 || tmp > 1)
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
