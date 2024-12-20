/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:57:46 by panger            #+#    #+#             */
/*   Updated: 2024/02/27 11:45:46 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_plane(t_ray ray, t_plane *plane)
{
	double		a;
	double		x;

	a = vec_dot(plane->vectors, ray.vector);
	if (a != 0)
	{
		x = (vec_dot(plane->vectors, \
		vec_substract(plane->coords, ray.origin))) / a;
		if (x > 0)
			return (x);
	}
	return (0);
}
