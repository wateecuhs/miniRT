/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:57:46 by panger            #+#    #+#             */
/*   Updated: 2024/02/26 12:58:52 by panger           ###   ########.fr       */
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
		x = (vec_dot(plane->vectors, vec_substract(plane->coords, ray.origin))) / a;
		if (x > 0)
			return (x);
	}
	return (0);
}
