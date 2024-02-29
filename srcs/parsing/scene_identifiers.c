/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:55:04 by panger            #+#    #+#             */
/*   Updated: 2024/02/29 11:31:10 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ambient	*ambient_identifier(char **line, int *error_status)
{
	t_ambient	*ret;
	double		tmp;

	*error_status = 0;
	if (ft_arrlen(line) != 3 || !is_float(line[1]))
		return (*error_status = 1, NULL);
	ret = (t_ambient *)malloc(sizeof(t_ambient));
	if (!ret)
		return (*error_status = 2, perror_prefix("malloc"), NULL);
	tmp = ft_atof(line[1]);
	if (tmp > 1 || tmp < 0)
		return (*error_status = 1, free(ret), NULL);
	ret->ratio = tmp;
	if (!get_rgb(line[2], &(ret->color)))
		return (*error_status = 1, free(ret), NULL);
	return (ret);
}

t_light	*light_identifier(char **line, int *error_status)
{
	t_light	*ret;
	double	tmp;

	*error_status = 0;
	if (ft_arrlen(line) != 4 || !is_float(line[2]))
		return (*error_status = 1, NULL);
	ret = (t_light *)malloc(sizeof(t_light));
	if (!ret)
		return (*error_status = 2, perror_prefix("malloc"), NULL);
	tmp = ft_atof(line[2]);
	if (tmp > 1 || tmp < 0)
		return (*error_status = 1, free(ret), NULL);
	ret->brightness = tmp;
	if (!get_coords(line[1], &(ret->coords)))
		return (*error_status = 1, free(ret), NULL);
	if (!get_rgb(line[3], &(ret->color)))
		return (*error_status = 1, free(ret), NULL);
	return (ret);
}

t_camera	*camera_identifier(char **line, int *error_status)
{
	t_camera	*ret;
	int			tmp;

	*error_status = 0;
	if (ft_arrlen(line) != 4)
		return (*error_status = 1, NULL);
	ret = (t_camera *)malloc(sizeof(t_camera));
	if (!ret)
		return (*error_status = 2, perror_prefix("malloc"), NULL);
	tmp = ft_atoi(line[3]);
	if (tmp < 0 || tmp > 180)
		return (*error_status = 1, free(ret), NULL);
	ret->fov = tmp;
	if (!get_coords(line[1], &(ret->coords)))
		return (*error_status = 1, free(ret), NULL);
	if (!get_vector(line[2], &(ret->vectors)))
		return (*error_status = 1, free(ret), NULL);
	vec_normalize(&ret->vectors);
	return (ret);
}
