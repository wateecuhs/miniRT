/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_C_L_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:55:04 by panger            #+#    #+#             */
/*   Updated: 2024/02/02 14:14:10 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ambient	*ambient_identifier(char **line)
{
	t_ambient	*ret;

	if (ft_arrlen(line) != 3 || !is_float(line[1]))
		return (NULL);
	ret = (t_ambient *)malloc(sizeof(t_ambient));
	if (!ret)
		return (perror_prefix("malloc"), NULL);
	ret->ratio = ft_atof(line[1]);
	if (!get_rgb(line[2], &(ret->color)))
		return (free(ret), NULL);
	return (ret);
}

t_light	*light_identifier(char **line)
{
	t_light	*ret;

	if (ft_arrlen(line) != 4 || !is_float(line[2]))
	{
		printf("%d\n", ft_arrlen(line));
		return (NULL);
	}
	ret = (t_light *)malloc(sizeof(t_light));
	if (!ret)
		return (perror_prefix("malloc"), NULL);
	ret->brightness = ft_atof(line[2]);
	if (!get_coords(line[2], &(ret->coords)))
		return (free(ret), NULL);
	if (!get_rgb(line[2], &(ret->color)))
		return (free(ret), NULL);
	printf("%d %d %d\n", ret->color.r, ret->color.g, ret->color.b);
	printf("%f %f %f\n", ret->coords.x, ret->coords.y, ret->coords.z);
	return (ret);
}
