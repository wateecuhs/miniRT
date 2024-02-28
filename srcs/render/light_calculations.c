/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:53:08 by panger            #+#    #+#             */
/*   Updated: 2024/02/28 14:14:00 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	apply_light(t_colors color, double rgb[3])
{
	t_colors	ret;
	int			tmp;

	tmp =  rgb[0] * color.r;
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

int	intersect_spheres(t_ray ray, t_scene *scene)
{
	void	*tmp;
	double	ret;

	tmp = scene->sphere;
	while (tmp)
	{
		ret = intersect_sphere(ray, tmp);
		if (ret > 0)
		{
			if (vec_distance(ray.origin, vec_add(ray.origin, ray.vector, ret)) < vec_distance(ray.origin, scene->light->coords))
				return (1);
		}
		tmp = ((t_sphere *)tmp)->next;
	}
	return (0);
}

int	intersect_planes(t_ray ray, t_scene *scene)
{
	void	*tmp;
	double	ret;

	tmp = scene->plane;
	while (tmp)
	{
		ret = intersect_plane(ray, tmp);
		if (ret > 0)
		{
			if (vec_distance(ray.origin, vec_add(ray.origin, ray.vector, ret)) < vec_distance(ray.origin, scene->light->coords))
				return (1);
		}
		tmp = ((t_plane *)tmp)->next;
	}
	return (0);
}

int	intersect_cylinders(t_ray ray, t_scene *scene)
{
	void	*tmp;
	double	ret;

	tmp = scene->cylinder;
	while (tmp)
	{
		ret = intersect_cylinder(ray, tmp);
		if (ret > 0)
		{
			if (vec_distance(ray.origin, vec_add(ray.origin, ray.vector, ret)) < vec_distance(ray.origin, scene->light->coords))
				return (1);
		}
		tmp = ((t_cylinder *)tmp)->next;
	}
	return (0);
}

int	light_intersects(t_ray ray, t_scene *scene)
{
	if (intersect_spheres(ray, scene) || intersect_planes(ray, scene)
		|| intersect_cylinders(ray, scene))
		return (1);
	return (0);
}
