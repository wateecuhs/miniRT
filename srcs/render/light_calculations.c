/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:53:08 by panger            #+#    #+#             */
/*   Updated: 2024/02/26 12:59:14 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	apply_light(t_colors color, double rgb[3])
{
	t_colors	ret;

	ret.r = rgb[0] * color.r;
	ret.g = rgb[1] * color.g;
	ret.b = rgb[2] * color.b;
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

	normal = vec_substract(sphere->coords, ray.origin);
	if (vec_cos(ray.vector, normal) > 0)
		normal = vec_multiply(normal, -1);
	light = vec_substract(scene->light->coords, ray.origin);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	add_coeficient(&rgb, scene->ambient_light->ratio, scene->ambient_light->color);
	coef = vec_dot(normal, light);
	if (coef > 0 && light_intersects(create_ray(ray.origin, light), scene) == 0)
	{
		coef = vec_cos(normal, light) * scene->light->brightness;
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
	light = vec_substract(scene->light->coords, ray.origin);
	coef = vec_dot(normal, light);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	add_coeficient(&rgb, scene->ambient_light->ratio, scene->ambient_light->color);
	if (coef > 0 && light_intersects(create_ray(ray.origin, light), scene) == 0)
	{
		coef = vec_cos(normal, light) * scene->light->brightness;
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

	normal = vec_cos(ray.vector, plane->vectors) > 0 ? vec_multiply(plane->vectors, -1) : plane->vectors;
	light = vec_substract(scene->light->coords, ray.origin);
	coef = vec_dot(normal, light);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	add_coeficient(&rgb, scene->ambient_light->ratio, scene->ambient_light->color);
	if (coef > 0 && light_intersects(create_ray(ray.origin, light), scene) == 0)
	{
		coef = vec_cos(normal, light) * scene->light->brightness;
		add_coeficient(&rgb, coef, scene->light->color);
	}
	color = apply_light(color, rgb);
	return (color);
}
