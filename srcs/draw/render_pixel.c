/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:23:22 by panger            #+#    #+#             */
/*   Updated: 2024/02/24 17:58:36 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
