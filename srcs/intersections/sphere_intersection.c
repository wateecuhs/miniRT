/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:56:34 by panger            #+#    #+#             */
/*   Updated: 2024/02/24 17:56:57 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_vectors	dist;
	double		params[3];
	double		delta;
	double		closest;
	double		x[2];

	params[0] = vec_dot(ray.vector, ray.vector);
	dist = substract(ray.origin, sphere->coords);
	params[1] = 2 * vec_dot(ray.vector, dist);
	params[2] = vec_dot(dist, dist) - (sphere->diameter * sphere->diameter);
	delta = ((params[1] * params[1]) - 4 * (params[0] * params[2]));
	if (delta >= 0)
	{
		x[0] = (-params[1] - sqrtf(delta)) / (2 * params[0]);
		x[1] = (-params[1] + sqrtf(delta)) / (2 * params[0]);
		closest = INFINITY;
		if (x[0] > EPSILON && x[0] < INFINITY)
			closest = x[0];
		if (x[1] > EPSILON && x[1] < INFINITY)
			closest = x[1] < x[0] ? x[1] : closest;
		return (closest);
	}
	return (-1);
}
