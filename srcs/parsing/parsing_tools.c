/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:28:10 by panger            #+#    #+#             */
/*   Updated: 2024/02/29 11:20:57 by dcindrak         ###   ########.fr       */
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
		return (perror("malloc"), 0);
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

int	get_coords(char *str, t_vectors *ret)
{
	int		tmp;
	int		i;
	char	**arr;

	arr = ft_split(str, ",");
	if (!arr)
		return (perror("malloc"), 0);
	if (ft_arrlen(arr) != 3 || !is_float(arr[0]) || !is_float(arr[1])
		|| !is_float(arr[2]))
		return (0);
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

int	get_vector(char *str, t_vectors *ret)
{
	double	tmp;
	int		i;
	char	**arr;

	arr = ft_split(str, ",");
	if (!arr)
		return (perror("malloc"), 0);
	if (ft_arrlen(arr) != 3 || !is_float(arr[0]) || !is_float(arr[1])
		|| !is_float(arr[2]))
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

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	split_checked(char *str, char *identifier, size_t line)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (is_alpha(str[i]))
		{
			while (str[i] && is_alpha(str[i]))
				i++;
			ret++;
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			if (str[i + 1] == ',' || !str[i + 1] || str[i + 1] == '\n' || str[i
					- 1] == ' ' || str[i - 1] == '\t' || ret > 1)
				return (error_parsing(1, line, identifier), 0);
		i++;
	}
	return (1);
}
