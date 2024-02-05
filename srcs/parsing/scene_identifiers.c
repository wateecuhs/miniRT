/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_C_L_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:55:04 by panger            #+#    #+#             */
/*   Updated: 2024/02/05 11:01:17 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ambient	*ambient_identifier(char **line)
{
	t_ambient	*ret;
	float		tmp;

	if (ft_arrlen(line) != 3 || !is_float(line[1]))
		return (NULL);
	ret = (t_ambient *)malloc(sizeof(t_ambient));
	if (!ret)
		return (perror_prefix("malloc"), NULL);
	tmp = ft_atof(line[1]);
	if (tmp > 1 || tmp < 0)
		return (free(ret), NULL);
	ret->ratio = tmp;
	if (!get_rgb(line[2], &(ret->color)))
		return (free(ret), NULL);
	return (ret);
}

t_light	*light_identifier(char **line)
{
	t_light	*ret;
	float	tmp;

	if (ft_arrlen(line) != 4 || !is_float(line[2]))
		return (NULL);
	ret = (t_light *)malloc(sizeof(t_light));
	if (!ret)
		return (perror_prefix("malloc"), NULL);
	tmp = ft_atof(line[2]);
	if (tmp > 1 || tmp < 0)
		return (free(ret), NULL);
	ret->brightness = tmp;
	if (!get_coords(line[1], &(ret->coords)))
		return (free(ret), NULL);
	if (!get_rgb(line[3], &(ret->color)))
		return (free(ret), NULL);
	return (ret);
}

t_camera	*camera_identifier(char **line)
{
	t_camera	*ret;
	int			tmp;

	if (ft_arrlen(line) != 4)
		return (NULL);
	ret = (t_camera *)malloc(sizeof(t_camera));
	if (!ret)
		return (perror_prefix("malloc"), NULL);
	tmp = ft_atoi(line[3]);
	if (tmp < 0 || tmp > 180)
		return (free(ret), NULL);
	ret->fov = tmp;
	if (!get_coords(line[1], &(ret->coords)))
		return (free(ret), NULL);
	if (!get_vector(line[2], &(ret->vectors)))
		return (free(ret), NULL);
	return (ret);
}
