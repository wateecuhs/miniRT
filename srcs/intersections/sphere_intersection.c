/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:56:34 by panger            #+#    #+#             */
/*   Updated: 2024/02/29 10:47:51 by panger           ###   ########.fr       */
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
	dist = vec_substract(ray.origin, sphere->coords);
	params[1] = 2 * vec_dot(ray.vector, dist);
	params[2] = vec_dot(dist, dist) - (sphere->diameter * sphere->diameter);
	delta = ((params[1] * params[1]) - 4 * (params[0] * params[2]));
	if (delta >= 0)
	{
		x[0] = (-params[1] - sqrtf(delta)) / (2 * params[0]);
		x[1] = (-params[1] + sqrtf(delta)) / (2 * params[0]);
		closest = 0;
		if (x[0] > EPSILON && x[1] > EPSILON)
			closest = x[0] < x[1] ? x[0] : x[1];
		else if (x[1] > EPSILON)
			closest = x[1];
		else if (x[0] > EPSILON)
			closest = x[0];
		return (closest);
	}
	return (-1);
}
