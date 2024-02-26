/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_identifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:12:32 by panger            #+#    #+#             */
/*   Updated: 2024/02/26 12:34:16 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_sphere	*sphere_identifier(char **line, int *error_status)
{
	t_sphere	*ret;

	*error_status = 0;
	if (ft_arrlen(line) != 4 || !is_float(line[2]))
		return (*error_status = 1, NULL);
	ret = (t_sphere *)malloc(sizeof(t_sphere));
	if (!ret)
		return (perror_prefix("malloc"), NULL);
	ret->next = NULL;
	ret->diameter = ft_atof(line[2]);
	if (!get_coords(line[1], &(ret->coords)))
		return (*error_status = 1, free(ret), NULL);
	if (!get_rgb(line[3], &(ret->color)))
		return (*error_status = 1, free(ret), NULL);
	return (ret);
}

t_plane	*plane_identifier(char **line, int *error_status)
{
	t_plane	*ret;

	*error_status = 0;
	if (ft_arrlen(line) != 4)
		return (*error_status = 1, NULL);
	ret = (t_plane *)malloc(sizeof(t_plane));
	if (!ret)
		return (perror_prefix("malloc"), NULL);
	ret->next = NULL;
	if (!get_coords(line[1], &(ret->coords)))
		return (*error_status = 1, free(ret), NULL);
	if (!get_vector(line[2], &(ret->vectors)))
		return (*error_status = 1, free(ret), NULL);
	if (!get_rgb(line[3], &(ret->color)))
		return (*error_status = 1, free(ret), NULL);
	return (ret);
}

t_cylinder	*cylinder_identifier(char **line, int *error_status)
{
	t_cylinder	*ret;

	*error_status = 0;
	if (ft_arrlen(line) != 6 || !is_float(line[3]) || !is_float(line[4]))
		return (*error_status = 1, NULL);
	ret = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!ret)
		return (perror_prefix("malloc"), NULL);
	ret->next = NULL;
	ret->vectors = create_vector(0, 0, 0);
	ret->diameter = ft_atof(line[3]);
	ret->height = ft_atof(line[4]);
	if (!get_coords(line[1], &(ret->coords)))
		return (*error_status = 1, free(ret), NULL);
	if (!get_vector(line[2], &(ret->vectors)))
		return (*error_status = 1, free(ret), NULL);
	if (!get_rgb(line[5], &(ret->color)))
		return (*error_status = 1, free(ret), NULL);
	return (ret);
}
