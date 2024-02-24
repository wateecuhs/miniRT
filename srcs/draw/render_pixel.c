/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:23:22 by panger            #+#    #+#             */
/*   Updated: 2024/02/24 16:32:20 by panger           ###   ########.fr       */
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

double	intersect_plane(t_ray ray, t_plane *plane)
{
	double		a;
	double		x;

	a = vec_dot(plane->vectors, ray.vector);
	if (a != 0)
	{
		x = (vec_dot(plane->vectors, substract(plane->coords, ray.origin))) / a;
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

double		mod(t_vectors v)
{
	return (sqrt(vec_dot(v, v)));
}

double		vcos(t_vectors a, t_vectors b)
{
	return (vec_dot(a, b) / (mod(a) * mod(b)));
}

t_colors	add_colors(t_colors color1, t_colors color2, double coef)
{
	t_colors	ret;
	int			tmp;

	tmp = color2.r + (color1.r * coef);
	if (tmp > 255)
		ret.r = 255;
	else
		ret.r = tmp;
	tmp = color2.g + (color1.g * coef);
	if (tmp > 255)
		ret.g = 255;
	else
		ret.g = tmp;
	tmp = color2.b + (color1.b * coef);
	if (tmp > 255)
		ret.b = 255;
	else
		ret.b = tmp;
	return (ret);
}

void	add_coeficient(double (*rgb)[3], double coef, t_colors color)
{
	(*rgb)[0] += coef * color.r / 255;
	(*rgb)[1] += coef * color.g / 255;
	(*rgb)[2] += coef * color.b / 255;
}

t_colors	apply_light(t_colors color, double rgb[3])
{
	t_colors	ret;
	int			tmp;

	if (rgb[0] >= 1 && rgb[1] >= 1 && rgb[2] >= 1)
		printf("SALUT\n");
	tmp = rgb[0] * color.r;
	if (tmp > 255)
		ret.r = 255;
	else
		ret.r = tmp;
	tmp = rgb[1] * color.g;
	if (tmp > 255)
		ret.g = 255;
	else
		ret.g = tmp;
	tmp = rgb[2] * color.b;
	if (tmp > 255)
		ret.b = 255;
	else
		ret.b = tmp;
	return (ret);
}

int	light_intersects(t_ray ray, t_scene *scene)
{
	void		*tmp;
	double		closest;
	double		ret;

	tmp = scene->sphere;
	closest = INFINITY;
	while (tmp)
	{
		ret = intersect_sphere(ray, tmp);
		if (ret < closest && ret > 0)
			return (1);
		tmp = ((t_sphere *)tmp)->next;
	}
	tmp = scene->plane;
	while (tmp)
	{
		ret = intersect_plane(ray, tmp);
		if (ret < closest && ret > 0)
			return (1);
		tmp = ((t_plane *)tmp)->next;
	}
	tmp = scene->cylinder;
	while (tmp)
	{
		ret = intersect_cylinder(ray, tmp);
		if (ret < closest && ret > 0)
			return (1);
		tmp = ((t_cylinder *)tmp)->next;
	}
	return (0);
}

t_colors	light_calculation_sphere(t_ray ray, t_scene *scene, t_colors color, t_sphere *sphere)
{
	t_vectors	light;
	double		coef;
	t_vectors	normal;
	double		rgb[3];

	normal = substract(sphere->coords, ray.origin);
	if (vcos(ray.vector, normal) > 0)
		normal = multiply_vector(normal, -1);
	light = substract(scene->light->coords, ray.origin);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	add_coeficient(&rgb, scene->ambient_light->ratio, scene->ambient_light->color);
	coef = vec_dot(normal, light);
	if (coef > 0 && light_intersects(create_ray(ray.origin, light), scene) == 0)
	{
		coef = vcos(normal, light) * scene->light->brightness;
		add_coeficient(&rgb, coef, scene->light->color);
	}
	color = apply_light(color, rgb);
	return (color);
}

t_colors	light_calculation_cylinder(t_ray ray, t_scene *scene, t_colors color, t_cylinder *cylinder)
{
	t_vectors	light;
	double		coef;
	t_vectors	normal;
	double		rgb[3];

	normal = cylinder->normal;
	light = substract(scene->light->coords, ray.origin);
	coef = vec_dot(normal, light);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	add_coeficient(&rgb, scene->ambient_light->ratio, scene->ambient_light->color);
	if (coef > 0 && light_intersects(create_ray(ray.origin, light), scene) == 0)
	{
		coef = vcos(normal, light) * scene->light->brightness;
		printf("%f\n", coef);
		add_coeficient(&rgb, coef, scene->light->color);
	}
	color = apply_light(color, rgb);
	return (color);
}

t_colors	light_calculation_plane(t_ray ray, t_scene *scene, t_colors color, t_plane *plane)
{
	t_vectors	light;
	double		coef;
	t_vectors	normal;
	double		rgb[3];

	normal = vcos(ray.vector, plane->vectors) > 0 ? multiply_vector(plane->vectors, -1) : plane->vectors;
	light = substract(scene->light->coords, ray.origin);
	coef = vec_dot(normal, light);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	add_coeficient(&rgb, scene->ambient_light->ratio, scene->ambient_light->color);
	if (coef > 0 && light_intersects(create_ray(ray.origin, light), scene) == 0)
	{
		coef = vcos(normal, light) * scene->light->brightness;
		add_coeficient(&rgb, coef, scene->light->color);
	}
	color = apply_light(color, rgb);
	return (color);
}

t_colors	get_all_intersections(t_ray ray, t_scene *scene)
{
	void		*tmp;
	double		closest;
	double		ret;
	t_colors	color;

	tmp = scene->sphere;
	closest = INFINITY;
	color = assign_color(0x000000);
	while (tmp)
	{
		ret = intersect_sphere(ray, tmp);
		if (ret < closest && ret > 0)
		{
			closest = ret;
			color = ((t_sphere *)tmp)->color;
			color = light_calculation_sphere(create_ray(add_coords_vectors(ray.origin, ray.vector, closest), ray.vector), scene, color, tmp);
		}
		tmp = ((t_sphere *)tmp)->next;
	}
	tmp = scene->plane;
	while (tmp)
	{
		ret = intersect_plane(ray, tmp);
		if (ret < closest && ret > 0)
		{
			closest = ret;
			color = ((t_plane *)tmp)->color;
			color = light_calculation_plane(create_ray(add_coords_vectors(ray.origin, ray.vector, closest), ray.vector), scene, color, tmp);
		}
		tmp = ((t_plane *)tmp)->next;
	}
	tmp = scene->cylinder;
	while (tmp)
	{
		ret = intersect_cylinder(ray, tmp);
		if (ret < closest && ret > 0)
		{
			closest = ret;
			color = ((t_cylinder *)tmp)->color;
			color = light_calculation_cylinder(create_ray(add_coords_vectors(ray.origin, ray.vector, closest), ray.vector), scene, color, tmp);
		}
		tmp = ((t_cylinder *)tmp)->next;
	}
	return (color);
}

int	render_pixel(t_mlx *mlx, int x, int y)
{
	t_ray		ray;
	t_colors	colors;

	ray = ray_to_pixel(x, y, mlx->scene);
	colors = get_all_intersections(ray, mlx->scene);
	draw_pixel(mlx->img->buffer, calc_pixel(x, y, mlx->img),
		colors, mlx->img->endian);
	return (1);
}
