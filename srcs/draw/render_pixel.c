/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:23:22 by panger            #+#    #+#             */
/*   Updated: 2024/02/23 19:03:00 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	assign_color(__uint32_t color)
{
	t_colors	ret;

	ret.a = color >> 24;
	ret.r = color >> 16;
	ret.g = color >> 8;
	ret.b = color >> 0;
	return (ret);
}

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

double	intersect_plane(t_ray ray, t_plane *plane)
{
	double		a;
	double		x;

	a = vec_dot(plane->vectors, ray.vector);
	if (a != 0)
	{
		x = (vec_dot(plane->vectors, substract(plane->coords, ray.origin))) / a;
		if (x > 0)
		{
			return (x);
		}
	}
	return (0);
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

	printf("%f\n", coef);
	tmp = color1.r + (color2.r * coef);
	printf("COLROS %d %d\n", color1.r, color2.r);
	printf("%d\n", tmp);
	if (tmp > 255)
		ret.r = 255;
	else
		ret.r = tmp;
	tmp = color1.g + (color2.g * coef);
	printf("%d\n", tmp);
	if (tmp > 255)
		ret.g = 255;
	else
		ret.g = tmp;
	tmp = color1.b + (color2.b * coef);
	printf("%d\n", tmp);
	if (tmp > 255)
		ret.b = 255;
	else
		ret.b = tmp;
	return (ret);
}

int		color_x_light(int color, double rgb[3])
{
	unsigned int	mask;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	mask = 255 << 16;
	r = rgb[0] * ((color & mask) >> 16);
	mask >>= 8;
	g = rgb[1] * ((color & mask) >> 8);
	mask >>= 8;
	b = rgb[2] * (color & mask);
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;
	return ((r << 16) | (g << 8) | b);
}

t_colors	light_calculation_sphere(t_ray ray, t_scene *scene, t_colors color, t_sphere *sphere)
{
	t_vectors	light;
	double		coef;
	t_vectors	normal;
	t_colors	rgb;

	normal = substract(sphere->coords, ray.origin);
	if (vcos(ray.vector, normal) > 0)
		normal = multiply_vector(normal, -1);
	light = substract(scene->light->coords, ray.origin);
	rgb = create_color(0, 0, 0, 0);
	rgb = multiply_colors(rgb, scene->ambient_light->color, scene->ambient_light->ratio);
	coef = vec_dot(normal, light);
	if (coef > 0)
	{
		coef = vcos(normal, light) * scene->light->brightness;
		printf("coef %f\n", coef);
		rgb = multiply_colors(rgb, scene->light->color, coef);
		color = add_colors(color, rgb, 1);
	}
	return (color);
}

t_colors	light_calculation(t_ray ray, t_scene *scene, t_colors color, t_plane *plane)
{
	t_vectors	light;
	double		coef;
	t_vectors	normal;
	t_colors	rgb;

	normal = vcos(ray.vector, plane->vectors) > 0 ? multiply_vector(plane->vectors, -1) : plane->vectors;
	light = substract(scene->light->coords, ray.origin);
	coef = vec_dot(normal, light);
	rgb = create_color(0, 0, 0, 0);
	rgb = multiply_colors(rgb, scene->ambient_light->color, scene->ambient_light->ratio);
	if (coef > 0)
	{
		coef = coef / (mod(normal) * mod(light));
		printf("%d %d %d\n", rgb.r, rgb.g, rgb.b);
		rgb = multiply_colors(rgb, scene->light->color, coef * scene->light->brightness);
		color = add_colors(color, rgb, 1);
	}
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
			color = light_calculation(create_ray(add_coords_vectors(ray.origin, ray.vector, closest), ray.vector), scene, color, tmp);
		}
		tmp = ((t_plane *)tmp)->next;
	}
	return (color);
}

int	render_pixel(t_mlx *mlx, int x, int y)
{
	t_ray		ray;
	t_colors	colors;

	ray = ray_to_pixel(x, y, mlx->scene);
	colors = get_all_intersections(ray, mlx->scene);
	// draw_pixel(mlx->img->buffer, calc_pixel(x, y, mlx->img),
	// 		add_ambient(assign_color(0x53FF45), mlx->scene->ambient_light), mlx->img->endian);
	draw_pixel(mlx->img->buffer, calc_pixel(x, y, mlx->img),
		colors, mlx->img->endian);
	return (1);
}
