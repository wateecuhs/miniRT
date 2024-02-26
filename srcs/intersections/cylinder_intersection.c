/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:58:43 by panger            #+#    #+#             */
/*   Updated: 2024/02/24 17:58:55 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	solve_cap(t_ray ray, t_vectors center, t_vectors normal)
{
	double		a;
	double		x;

	a = vec_dot(normal, ray.vector);
	if (a != 0)
	{
		x = (vec_dot(normal, substract(center, ray.origin))) / a;
		if (x > 0)
			return (x);
	}
	return (0);
}

int	solve_cylinder(t_ray ray, t_cylinder *cylinder, double x[2])
{
	t_vectors	v;
	t_vectors	u;
	double		params[3];
	double		delta;

	v = substract(ray.vector, multiply_vector(cylinder->vectors, vec_dot(ray.vector, cylinder->vectors)));
	u = substract(substract(ray.origin, cylinder->coords), multiply_vector(cylinder->vectors, vec_dot(substract(ray.origin, cylinder->coords), cylinder->vectors)));
	params[0] = vec_dot(v, v);
	params[1] = 2 * vec_dot(v, u);
	params[2] = vec_dot(u, u) - (cylinder->diameter * cylinder->diameter);
	delta = ((params[1] * params[1]) - 4 * (params[0] * params[2]));
	x[0] = (-params[1] - sqrtf(delta)) / (2 * params[0]);
	x[1] = (-params[1] + sqrtf(delta)) / (2 * params[0]);
	if ((x[0] > EPSILON && x[0] < INFINITY) || (x[1] > EPSILON && x[1] < INFINITY))
		return (1);
	return (0);
}

t_vectors	get_cylinder_normal(t_ray ray, t_cylinder *cylinder, double distances[2], double x[2])
{
	double	dist;
	double	tmp;

	if ((distances[0] >= 0 && distances[0] <= cylinder->height && distances[0] > EPSILON)
		&& (distances[1] >= 0 && distances[1] <= cylinder->height && distances[1] > EPSILON))
	{
		dist = x[0] < x[1] ? distances[0] : distances[1];
		tmp = x[0] < x[1] ? x[0] : x[1];
	}
	else if (distances[0] >= 0 && distances[0] <= cylinder->height && distances[0] > EPSILON)
	{
		dist = distances[0];
		tmp = x[0];
	}
	else
	{
		dist = distances[1];
		tmp = x[1];
	}
	x[0] = tmp;
	return (substract(substract(multiply_vector(ray.vector, x[0]), multiply_vector(cylinder->vectors, dist)), substract(cylinder->coords, ray.origin)));
}

double	caps_intersection(t_ray ray, t_cylinder *cylinder)
{
	t_vectors	top_cap;
	t_vectors	inters[2];
	double		distances[2];
	double		tmp;

	top_cap = add_coords_vectors(cylinder->coords, cylinder->vectors, cylinder->height);
	distances[0] = solve_cap(ray, cylinder->coords, cylinder->vectors);
	distances[1] = solve_cap(ray, top_cap, cylinder->vectors);
	if (distances[0] < INFINITY || distances[1] < INFINITY)
	{
		inters[0] = add_coords_vectors(ray.origin, ray.vector, distances[0]);
		inters[1] = add_coords_vectors(ray.origin, ray.vector, distances[1]);
		if (distances[0] < INFINITY && vector_distance(inters[0], cylinder->coords) < cylinder->diameter
			&& distances[1] < INFINITY && vector_distance(inters[1], top_cap) < cylinder->diameter)
			return (distances[0] < distances[1] ? distances[0] : distances[1]);
		else if (distances[0] < INFINITY && vector_distance(inters[0], cylinder->coords) < cylinder->diameter)
			return (distances[0]);
		else if (distances[1] < INFINITY && vector_distance(inters[1], top_cap) < cylinder->diameter)
			return (distances[1]);
	}
	return (INFINITY);
}

double	intersect_cylinder(t_ray ray, t_cylinder *cylinder)
{
	double		distances[2];
	double		x[2];

	if (solve_cylinder(ray, cylinder, x) == 0)
		return (INFINITY);
	distances[0] = vec_dot(cylinder->vectors, substract(multiply_vector(ray.vector, x[0]), substract(cylinder->coords, ray.origin)));
	distances[1] = vec_dot(cylinder->vectors, substract(multiply_vector(ray.vector, x[1]), substract(cylinder->coords, ray.origin)));
	if (!((distances[0] >= 0 && distances[0] <= cylinder->height && x[0] > EPSILON)
		|| (distances[1] >= 0 && distances[1] <= cylinder->height && x[1] > EPSILON)))
		return (INFINITY);
	cylinder->normal = get_cylinder_normal(ray, cylinder, distances, x);
	x[1] = caps_intersection(ray, cylinder);
	if (x[1] < x[0])
	{
		cylinder->normal = cylinder->vectors;
		return (x[1]);
	}
	return (x[0]);
}
